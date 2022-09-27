#include "config.h"

#include "Indications.h"
#include "ThermoRegulation.h"
#include "Logger.h"

ThermoRegulator thermoRegulator(NEEDED_THERMOREGULATOR_TEMP_C);
Logger logger;

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

  logger.setLoggingDelay(LOGGING_MILLIS_DELAY);
  logger.addColumn(String("Thermoregulation ntc (*C)"), [=]() -> float { 
    return thermoRegulator.getNtc().getTempAverage();
  });

  logger.startLogging();
}

void loop() {
  indicate();
  thermoRegulator.regulate();
  logger.logOnTimer();
}
