#include "Executables.h"

#include <Arduino.h>
#include <Servo.h>
#include "config.h"

Servo servos[ARRAY_SIZE(SERVOS_PINS)];

void setupExecutables() {
    for (int i = 0; i < ARRAY_SIZE(SERVOS_PINS); ++i) {
        servos[i].attach(SERVOS_PINS[i]);
    }

    resetServos();
    resetFuses();
}

void resetServos() {
    for (int i = 0; i < ARRAY_SIZE(SERVOS_DEFAULT_POSITIONS); ++i) {
        servos[i].write(SERVOS_DEFAULT_POSITIONS[i]);
    }
}

void resetFuses() {

}

void activateServos() {
    for (int i = 0; i < ARRAY_SIZE(SERVOS_ACTIVATED_POSITIONS); ++i) {
        servos[i].write(SERVOS_ACTIVATED_POSITIONS[i]);
    }
}

void activateFuses() {

}

bool getServosState() {

}

bool getFusesState() {

}
