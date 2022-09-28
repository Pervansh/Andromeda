#pragma once

#include <Arduino.h>

void setupExecutables();

void resetServos();
void resetFuses();

void activateServos();
void activateFuses();
void activateOneFuse(uint8_t id);

bool getServosState();
bool getFusesState();
