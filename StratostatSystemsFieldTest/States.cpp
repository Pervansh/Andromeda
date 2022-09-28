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

StateSequence& getStateSequence() {
    return stateSequence;
}

Logger&  getStateLogger() {
    return stateLogger;
}

bool toNextState(void*) {
    stateSequence.toNext();
    return true;
}

namespace States {

unsigned long waitingApogeeFallingTime;

void setupUp() {
    setupIndications();
    setupOrientationDetermination();
    setupExecutables();

    stateSequence.toNext();
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

    if (ax * ax + ay * ay + az * az <= FALLING_ACCELERATION_UPPER_BOUND) {
        waitingApogeeFallingTime += delay;
    } else {
        waitingApogeeFallingTime = 0;
    }

    if (waitingApogeeFallingTime >= WAITING_APOGEE_TRIGGER_FALLING_TIME) {
        stateSequence.toNext();
    }

    return true;
}

void activateExecutables() {
    activateServos();

    stateSequence.getTimer().in(2000, [](void*) -> bool {
        resetServos();
        toNextState();
        return true;
    });
}

void waitingLanding() {
    stateSequence.toNext();
}

void onLanding() {
    changeBuzzerIndication(500, 1000, 3);
}

}
