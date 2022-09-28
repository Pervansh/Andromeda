#include "StateSequence.h"

#include <Arduino.h>

StateSequence::StateSequence() : size(0), current(0), wasStarted(false) {
    auto empty = [](){};
    for (int i = 0; i < STATE_SEQUENCE_MAX_SIZE; ++i) {
        members[i] = empty;
    }
}

StateSequence& StateSequence::addNext(StateFunction newMember) {
    if (size < STATE_SEQUENCE_MAX_SIZE) {
        members[size] = newMember;
        size++;

    } else {
        Serial.println("Can't add next member to sequence! StateSequence's size equals STATE_SEQUENCE_MAX_SIZE!");
    }

    return (*this);
}

void StateSequence::toNext() {
    if (wasStarted) {
        if (current + 1 < size) {
            timer.cancel();
            current++;
            members[current]();
        
        } else {
            Serial.println("Can't go to next member of sequence! Last state is last in the sequence!");
        }

    } else {
        Serial.println("Can't go to next member of sequence! StateSequence wasn't started!");
    }
}

void StateSequence::start() {
    timer.cancel();
    current = 0;
    wasStarted = true;
    members[current]();
}

void StateSequence::stop() {
    timer.cancel();
    wasStarted = false;
}

