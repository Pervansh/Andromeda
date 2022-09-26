#ifndef THERMO_REGULATION_H
#define THERMO_REGULATION_H

#include <GyverNTC.h>
#include <GyverPID.h>
#include <PIDtuner.h>
#include <PIDtuner2.h>

#include "config.h"

class ThermoRegulator {
private:
  GyverPID pid = GyverPID(PID_COEFFICIENTS[0], PID_COEFFICIENTS[1], PID_COEFFICIENTS[2]);
  GyverNTC ntc = GyverNTC(THERMOREGULATION_THERMISTOR_PIN, 10000, 3435);
  bool isTurnedOn;

public:
  ThermoRegulator(float neededTempC);

  void regulate();

  void turnOn ();
  void turnOff();

  void changeNeededTemperature(float tempC);

  ~ThermoRegulator();
};

#endif  // THERMO_REGULATION_H