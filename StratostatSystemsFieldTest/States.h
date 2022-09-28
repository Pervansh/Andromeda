#pragma once

#include "StateSequence.h"
#include "Logger.h"

StateSequence& getStateSequence();
Logger&        getStateLogger();

bool toNextState(void* = nullptr);
void statesTick();

namespace States {

void setupUp();
void prelaunchWork();
void launched();
bool waitingApogee(void* codedDelay);
void activateExecutables();
void waitingLanding();
void onLanding();

}
