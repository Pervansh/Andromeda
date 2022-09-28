#pragma once

#include "config.h"

#include <arduino-timer.h>

class StateSequence {
public:
    using StateTimer    = Timer<STATE_TIMER_TASK_MAX_COUNT, millis>;
    using StateFunction = void (*)();

private:
    uint8_t size;
    uint8_t current;
    bool wasStarted;
    StateFunction members[STATE_SEQUENCE_MAX_SIZE];

    StateTimer timer;
public:
    StateSequence();

    StateSequence& addNext(StateFunction newMember);
    
    void toNext();
    void start();
    void stop();
    
    StateTimer& getTimer() { return timer; }
};
