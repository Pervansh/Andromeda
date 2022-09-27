#include "Arduino.h"
#include "ThermoRegulation.h"

#include "config.h"

ThermoRegulator::ThermoRegulator(float neededTempC) {
  pid.setLimits(0, 255);

  pinMode(THERMOREGULATOR_PIN, OUTPUT);
  
  isTurnedOn = false;
}

void ThermoRegulator::regulate() {
  int output;
  
  if (isTurnedOn) {
    pid.input = ntc.getTempAverage();
    output = pid.getResultNow();
  } else {
    output = 0;
  }

  analogWrite(THERMOREGULATOR_PIN, output);
}

void ThermoRegulator::turnOn() {
  pid.getResultNow();
  isTurnedOn = true;
}

void ThermoRegulator::turnOff() {
  isTurnedOn = false;
    analogWrite(THERMOREGULATOR_PIN, 0);
}

void ThermoRegulator::changeNeededTemperature(float tempC) {
  pid.setpoint = tempC;
}

const GyverNTC& ThermoRegulator::getNtc() {
  return ntc;
}

ThermoRegulator::~ThermoRegulator() {
  turnOff();
}
