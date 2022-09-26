#include "Arduino.h"
#include "ThermoRegulation.h"

#include "config.h"

ThermoRegulator::ThermoRegulator() {
  pid.setLimits(0, 255);

  pinMode(THERMOREGULATOR_PIN, OUTPUT);
  
  isTurnedOn = false;
}

void ThermoRegulator::regulate() {
  if (isTurnedOn) {
    analogWrite(THERMOREGULATOR_PIN, pid.getResultNow());
  }
}