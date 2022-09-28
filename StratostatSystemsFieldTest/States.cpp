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

    toNextState();
}

void prelaunchWork() {
    changeBuzzerIndication(200, 1000);

    stateSequence.getTimer().in(3000, toNextState);
}

void launched() {
    waitingApogeeFallingTime = 0;
    changeBuzzerIndication(400, 250);

    stateSequence.getTimer().every(1, waitingApogee, (void*)((unsigned long)1));
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

    Serial.println("Waiting apogee");

    return true;
}

void activateExecutables() {
    changeBuzzerIndication(0);
    activateServos();

    Serial.println("activate executables");

    stateSequence.getTimer().in(2000, [](void*) -> bool {
        resetServos();
        toNextState();

        Serial.println("deactivate executables");

        return true;
    });
}

void waitingLanding() {
    toNextState();
}

void onLanding() {
    changeBuzzerIndication(500, 1000, 3);
}

}
