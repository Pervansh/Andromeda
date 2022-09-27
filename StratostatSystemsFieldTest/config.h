#ifndef CONFIG_H
#define CONFIG_H

#include "forConfig.h"
/*
  Файл конфигурации
*/

// Перечисление параметров PARAMETER(*имя параметра*, *значение параметра*)
// Кол-во светодиодов
PARAMETER(LED_COUNT, 3)
PARAMETER(THERMOREGULATION_LED_ID, 0)

PARAMETER(NEEDED_THERMOREGULATOR_TEMP_C, 60.0)

PARAMETER(LOGGING_FILE_NAME, "log_tests")
PARAMETER(LOGGING_MILLIS_DELAY, 50)
PARAMETER(SD_CARD_CHIP_SELECT, BUILTIN_SDCARD)
PARAMETER(LOG_MAX_DATA_COLUMNS, 10)

// PARAMETER(BMP280_I2C_ADDRESS, 0x77)
PARAMETER(USE_MPU6050_DEFAULT_I2C_ADDRESS, true)
PARAMETER(MPU6050_INSTEAD_OF_DEFAULT_I2C_ADDRESS, 0x00)

PARAMETER(GPS_SERIAL_BAUD, 4800)

// Задание массивов ARRAY(*имя массива*, *тип элементов массива*, *кол-во элементов*, DATA(*элементы через запятую*))
ARRAY(PID_COEFFICIENTS, float, 3, DATA(1, 2, 3))

// Настройка пинов устройств SET_PIN(*смысловое имя пина/устройства*, *номер пина*)
SET_PIN(BUZZER, 2)
SET_PIN(LED_DATA, 35)
SET_PIN(THERMOREGULATOR, 20)
SET_PIN(LOG_THERMISTOR, 0)
SET_PIN(THERMOREGULATION_THERMISTOR, 0)
SET_PIN(GPS_RX, 4)
SET_PIN(GPS_TX, 3)

#endif  // CONFIG_H