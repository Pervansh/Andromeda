#pragma once

#include "StateSequence.h"
#include "Logger.h"
#include "ThermoRegulation.h"

StateSequence&   getStateSequence();
Logger&          getStateLogger();
ThermoRegulator& getStateThermoRegulator();

bool toNextState(void* = nullptr);
void startStateSequence();
void statesTick();

bool startStateLogger (void* number = nullptr);
bool finishStateLogger(void* = nullptr);

bool turnOnStateThermoRegulator (void* = nullptr);
bool turnOffStateThermoRegulator(void* = nullptr);

namespace States {

void setupUp();
void prelaunchWork();
void launched();
bool waitingApogee(void* codedDelay);
void activateExecutables();
void onLanding();
void landed();

}
