#include "config.h"

#include "Indications.h"
#include "ThermoRegulation.h"
#include "Logger.h"
#include "OrientationDetermination.h"
#include "Executables.h"

ThermoRegulator thermoRegulator(NEEDED_THERMOREGULATOR_TEMP_C);
Logger logger;

String sessionCode = LOGGING_FILE_NAME;
int loggingCycleCount = 0;

void setup() {
    Serial.begin(3600);
    delay(50);

    setupIndications();
    setupOrientationDetermination();

    logger.setLoggingDelay(LOGGING_MILLIS_DELAY);

    logger.addColumn(String("Thermoregulation ntc (*C)"), [=]() -> float { 
        return thermoRegulator.getNtc().getTempAverage();
    });
    logger.addColumn("Carbon temperature (*C)", &getCarbonTemperature);

    logger.addColumn(String("BmpAltitude (m)"), &getBmpAltitude);
    logger.addColumn(String("BmpPressure"), &getBmpPressure);

    logger.addColumn(String("AccX"), &getMpuAccelerationX);
    logger.addColumn(String("AccY"), &getMpuAccelerationY);
    logger.addColumn(String("AccZ"), &getMpuAccelerationZ);
    logger.addColumn(String("RotX"), &getMpuRotationX);
    logger.addColumn(String("RotY"), &getMpuRotationY);
    logger.addColumn(String("RotZ"), &getMpuRotationZ);

    logger.startLogging(sessionCode + ".txt");

    setupExecutables();

    delay(1500);
    activateServos();
    delay(1000);
    resetServos();

    delay(3000);
    activateOneFuse(0);
    delay(3000);
    resetFuses();

    delay(3000);
    activateOneFuse(1);
    delay(3000);
    resetFuses();

    delay(3000);
    activateOneFuse(2);
    delay(3000);
    resetFuses();
}

void loop() {
    updateGpsData();

    indicate();
    thermoRegulator.regulate();
    logger.logOnTimer();

    if (millis() >= 10000) {
        logger.finishLogging();
    } else {
        Serial.println("Logging");
    }
}
