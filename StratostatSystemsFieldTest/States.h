#pragma once

#include "StateSequence.h"
#include "Logger.h"

StateSequence& getStateSequence();
Logger&        getStateLogger();

void toNextState();

namespace States {

void setupUp();
void prelaunchWork();
void launched();
void waitingApogee(void* codedDelay);
void activateExecutables();
void waitingLanding();
void onLanding();

}
