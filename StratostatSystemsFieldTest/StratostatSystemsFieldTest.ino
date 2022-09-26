#include "config.h"

#include "Indications.h"
#include "ThermoRegulation.h"

ThermoRegulator thermoRegulator(NEEDED_THERMOREGULATOR_TEMP_C);

void setup() {
  Serial.begin(3600);
  delay(50);
  Serial.print(PID_COEFFICIENTS[0]);
  Serial.print(' ');
  Serial.print(PID_COEFFICIENTS[1]);
  Serial.print(' ');
  Serial.print(PID_COEFFICIENTS[2]);
  Serial.println();

  setupIndications();
}

void loop() {
  indicate();
  thermoRegulator.regulate();
}
