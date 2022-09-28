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

void activateOneFuse(uint8_t id) {
    if (id < ARRAY_SIZE(FUSES_PINS)) {
        digitalWrite(FUSES_PINS[id], FUSES_ACTIVATION_STATES[id]);
    } else {
        Serial.println("Can't ignate fuse! Fuse's Id (" + String(id) + ") is not less than count of fuses (" + String(ARRAY_SIZE(FUSES_PINS)) + ").");
    }
}

bool getServosState() {

}

bool getFusesState() {

}
