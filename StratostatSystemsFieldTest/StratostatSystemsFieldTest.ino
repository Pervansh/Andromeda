#include "config.h"

#include "Indications.h"
#include "ThermoRegulation.h"
#include "Logger.h"
#include "OrientationDetermination.h"
#include "Executables.h"
#include "States.h"
#include "StateSequence.h"

ThermoRegulator thermoRegulator(NEEDED_THERMOREGULATOR_TEMP_C, true);
Logger logger = getStateLogger();

String sessionCode = LOGGING_FILE_NAME;
int loggingCycleCount = 0;

void setup() {
    Serial.begin(3600);
    delay(50);

    getStateSequence().addNext(States::setupUp)
                      .addNext(States::prelaunchWork)
                      .addNext(States::launched)
                      .addNext(States::activateExecutables)
                      .addNext(States::onLanding)
                      .addNext(States::landed);

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

    thermoRegulator.turnOn();

    // startStateSequence();
}

void loop() {
    statesTick();
    indicate();

    thermoRegulator.regulate();
    Serial.print("Thermoregulation ntc (*C): ");
    Serial.println(thermoRegulator.getNtc().getTempAverage());

}
