#include "config.h"

#include "Indications.h"
#include "ThermoRegulation.h"

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
}
