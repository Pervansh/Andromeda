#ifndef THERMO_REGULATION_H
#define THERMO_REGULATION_H

#include <GyverNTC.h>
#include <GyverPID.h>
#include <PIDtuner.h>
#include <PIDtuner2.h>

#include "config.h"

float getCarbonTemperature();

class ThermoRegulator {
private:
  GyverPID pid = GyverPID(PID_COEFFICIENTS[0], PID_COEFFICIENTS[1], PID_COEFFICIENTS[2]);
  GyverNTC ntc = GyverNTC(THERMOREGULATION_THERMISTOR_PIN, 10000, 3435);
  bool isTurnedOn;
  bool useRelay;

public:
  ThermoRegulator(float neededTempC, bool _useRelay = false);

  void regulate();

  void turnOn ();
  void turnOff();

  void changeNeededTemperature(float tempC);

  const GyverNTC& getNtc();

  ~ThermoRegulator();
};

#endif  // THERMO_REGULATION_H