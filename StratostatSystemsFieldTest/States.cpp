#include "States.h"

#include <Arduino.h>
#include "Logger.h"
#include "Indications.h"
#include "Executables.h"
#include "OrientationDetermination.h"
#include "StateSequence.h"
#include "config.h"

StateSequence stateSequence;
Logger stateLogger;

bool isToNextState = false;

StateSequence& getStateSequence() {
    return stateSequence;
}

Logger&  getStateLogger() {
    return stateLogger;
}

bool toNextState(void*) {
    isToNextState = true;
    return true;
}

void startStateSequence() {
    stateSequence.start();
}

void statesTick() {
    stateSequence.getTimer().tick();

    if (isToNextState) {
        stateSequence.toNext();
        isToNextState = false;
    }
}

namespace States {

unsigned long waitingApogeeFallingTime;

void setupUp() {
    setupIndications();
    setupOrientationDetermination();
    setupExecutables();

    Serial.println("Setup done well");

    toNextState();
}

void prelaunchWork() {
    changeBuzzerIndication(200, 1000);

    Serial.println("Prelaunch works");

    stateSequence.getTimer().at(TOTALLY_LAUNCHED_AT, toNextState);
}

void launched() {
    waitingApogeeFallingTime = 0;
    changeBuzzerIndication(400, 250);

    Serial.println("Launched");

    stateSequence.getTimer().every(1, waitingApogee, (void*)((unsigned long)1));
    Serial.println("Now waiting apogee");
}

bool waitingApogee(void* codedDelay) {
    unsigned long delay = (unsigned long)codedDelay;
    auto ax = getMpuAccelerationX();
    auto ay = getMpuAccelerationY();
    auto az = getMpuAccelerationZ();

    if (ax * ax + ay * ay + az * az <= FALLING_ACCELERATION_UPPER_BOUND_SQ) {
        waitingApogeeFallingTime += delay;
    } else {
        waitingApogeeFallingTime = 0;
    }

    if (waitingApogeeFallingTime >= WAITING_APOGEE_TRIGGER_FALLING_TIME) {
        toNextState();
    }

    return true;
}

void activateExecutables() {
    setupExecutables();
    changeBuzzerIndication(0);

    Serial.println("Activating executables");
    
    stateSequence.getTimer().in(SERVOS_ACTIVATION_DELAY,
    [](void*) -> bool {
        activateServos();
        Serial.println("Activating servos");
        return true;
    });
    stateSequence.getTimer().in(SERVOS_ACTIVATION_DELAY + SERVOS_ACTIVATITY_TIME,
    [](void*) -> bool {
        Serial.println("Deactivating servos");
        resetServos();
        return true;
    });

    // Могут быть проблемы из-за отсутствия функции сброса только одного конкретного запала
    if (ACTIVATE_FUSES_AFTER_REACHING_APOGEE) {
        // ORDINARY_FUSE_1 ACT
        stateSequence.getTimer().in(ORDINARY_FUSE_1_ACTIVATION_DELAY,
        [](void) -> bool {
            activateOneFuse(ORDINARY_FUSE_1_ID);
            Serial.println("Activating ORDINARY_FUSE_1");
            return true;
        });
        stateSequence.getTimer().in(ORDINARY_FUSE_1_ACTIVATION_DELAY + EACH_NOT_HEATING_FUSE_ACTIVATITY_TIME,
        [](void) -> bool {
            resetFuses();
            Serial.println("Deactivating ORDINARY_FUSE_1");
            return true;
        });

        // ORDINARY_FUSE_2 ACT
        stateSequence.getTimer().in(ORDINARY_FUSE_2_ACTIVATION_DELAY,
        [](void) -> bool {
            activateOneFuse(ORDINARY_FUSE_2_ID);
            Serial.println("Activating ORDINARY_FUSE_2");
            return true;
        });
        stateSequence.getTimer().in(ORDINARY_FUSE_2_ACTIVATION_DELAY + EACH_NOT_HEATING_FUSE_ACTIVATITY_TIME,
        [](void) -> bool {
            resetFuses();
            Serial.println("Deactivating ORDINARY_FUSE_2");
            return true;
        });

        // HEATING_FUSE ACT
        stateSequence.getTimer().in(HEATING_FUSE_ACTIVATION_DELAY,
        [](void) -> bool {
            activateOneFuse(HEATING_FUSE_ID);
            Serial.println("Activating HEATING_FUSE");
            return true;
        });

        // WARMED_FUSE ACT 
        stateSequence.getTimer().in(HEATING_FUSE_ACTIVATION_DELAY + HEATING_FUSE_ACTIVATITY_TIME,
        [](void) -> bool {
            resetFuses();
            Serial.println("Deactivating HEATING_FUSE");
            activateOneFuse(WARMED_FUSE_ID);
            Serial.println("Activating WARMED_FUSE");
            return true;
        });
        stateSequence.getTimer().in(HEATING_FUSE_ACTIVATION_DELAY + HEATING_FUSE_ACTIVATITY_TIME + EACH_NOT_HEATING_FUSE_ACTIVATITY_TIME,
        [](void) -> bool {
            resetFuses();
            Serial.println("Deactivating WARMED_FUSE");
            return true;
        });
    }

    stateSequence.getTimer().in(MAX_ACTIVATION_TIME, [](void*) -> bool {
        resetServos();
        resetFuses();
        Serial.println("Deactivating all executables");
        toNextState();
        return true;
    });
}

void onLanding() {
    Serial.println("On landing");
    changeBuzzerIndication(200, 2000, 3);

    stateSequence.getTimer().in(TOTAL_LANDING_TIME, toNextState);
}

void landed() {
    changeBuzzerIndication(600, 1000);
    Serial.println("Landed");
}

}
