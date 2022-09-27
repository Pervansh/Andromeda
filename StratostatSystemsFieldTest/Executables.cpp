#include "Executables.h"

#include <Arduino.h>
#include <Servo.h>
#include "config.h"

Servo servos[ARRAY_SIZE(SERVOS_PINS)];

void setupExecutables() {
    COUNT_FOR(i, SERVOS_PINS) {
        servos[i].attach(SERVOS_PINS[i]);
    }
    resetServos();

    COUNT_FOR(i, FUSES_PINS) {
        pinMode(FUSES_PINS[i], OUTPUT);
    }
    resetFuses();
}

void resetServos() {
    COUNT_FOR(i, SERVOS_DEFAULT_POSITIONS) {
        servos[i].write(SERVOS_DEFAULT_POSITIONS[i]);
    }
}

void resetFuses() {
    COUNT_FOR(i, FUSES_ACTIVATION_STATES) {
        digitalWrite(FUSES_PINS[i], !FUSES_ACTIVATION_STATES[i]);
    }
}

void activateServos() {
    COUNT_FOR(i, SERVOS_ACTIVATED_POSITIONS) {
        servos[i].write(SERVOS_ACTIVATED_POSITIONS[i]);
    }
}

void activateFuses() {
    COUNT_FOR(i, FUSES_ACTIVATION_STATES) {
        digitalWrite(FUSES_PINS[i], FUSES_ACTIVATION_STATES[i]);
    }
}

bool getServosState() {

}

bool getFusesState() {

}
