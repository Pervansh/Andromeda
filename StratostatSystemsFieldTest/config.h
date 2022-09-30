#ifndef CONFIG_H
#define CONFIG_H

#include "forConfig.h"
/*
  Файл конфигурации
  Правили и замечания:
    1. Все названия и имена пишуться в верхнем регистре (КАПС-ЛОКОМ)
    2. Время по умолчанию указывается в миллисекундах
*/

// Перечисление параметров PARAMETER(*имя параметра*, *значение параметра*)
// Задание массивов ARRAY(*имя массива*, *тип элементов массива*, *кол-во элементов*, DATA(*элементы через запятую*))

// Индикация
PARAMETER(LED_COUNT, 3)
PARAMETER(THERMOREGULATION_LED_ID, 0)

// Терморегуляция
PARAMETER(NEEDED_THERMOREGULATOR_TEMP_C, 20.0)
PARAMETER(THERMOREGULATOR_PID_DIRECTION, REVERSE)  // (NORMAL, REVERSE)
ARRAY(PID_COEFFICIENTS, float, 3, DATA(29, 2.8, 74))
PARAMETER(TURN_ON_THERMOREGULATION_AT, MINUTES_TO_MILLIS(30))

// Логгирование
PARAMETER(LOGGING_FILE_NAME, "log_tests")
PARAMETER(LOGGING_MILLIS_DELAY, 50)
PARAMETER(SD_CARD_CHIP_SELECT, BUILTIN_SDCARD)
PARAMETER(LOG_MAX_DATA_COLUMNS, 15)
PARAMETER(NEW_LOG_FILE_CREATION_EVERY, MINUTES_TO_MILLIS(30))

// Барометр
// PARAMETER(BMP280_I2C_ADDRESS, 0x77)
PARAMETER(SEA_LEVEL_PRESSURE, 1015.0f)

// IMU
PARAMETER(USE_MPU6050_DEFAULT_I2C_ADDRESS, true)
PARAMETER(MPU6050_INSTEAD_OF_DEFAULT_I2C_ADDRESS, 0x00)
PARAMETER(FALLING_ACCELERATION_UPPER_BOUND, 1500)
PARAMETER(FALLING_ACCELERATION_UPPER_BOUND_SQ, FALLING_ACCELERATION_UPPER_BOUND * FALLING_ACCELERATION_UPPER_BOUND)
PARAMETER(WAITING_APOGEE_TRIGGER_FALLING_TIME, 50)

// GPS
PARAMETER(GPS_SERIAL_BAUD, 4800)

// Активируемые устройства (сервоприводы, запалы, нагреватель запала)
PARAMETER(ORDINARY_FUSE_1_ID, 0)
PARAMETER(ORDINARY_FUSE_2_ID, 1)
PARAMETER(WARMED_FUSE_ID,     2)
PARAMETER(HEATING_FUSE_ID,    3)
PARAMETER(ACTIVATE_FUSES_AFTER_REACHING_APOGEE, false)
PARAMETER(MAX_ACTIVATION_TIME, 50000)
PARAMETER(SERVOS_ACTIVATION_DELAY,    45000)
PARAMETER(SERVOS_ACTIVATITY_TIME,      2000)
PARAMETER(ORDINARY_FUSE_1_ACTIVATION_DELAY, 0)
PARAMETER(ORDINARY_FUSE_2_ACTIVATION_DELAY, 6000)
PARAMETER(HEATING_FUSE_ACTIVATION_DELAY,    19000)
PARAMETER(EACH_NOT_HEATING_FUSE_ACTIVATITY_TIME, 3000)
PARAMETER(HEATING_FUSE_ACTIVATITY_TIME,         20000)
ARRAY(SERVOS_PINS, int, 2, DATA(3, 4))
ARRAY(FUSES_PINS,  int, 4, DATA(36, 38, 37, 21))
ARRAY(SERVOS_DEFAULT_POSITIONS,   int, ARRAY_SIZE(SERVOS_PINS), DATA(0, 90))
ARRAY(SERVOS_ACTIVATED_POSITIONS, int, ARRAY_SIZE(SERVOS_PINS), DATA(90, 0))
ARRAY(FUSES_ACTIVATION_STATES, bool, ARRAY_SIZE(FUSES_PINS), DATA(true, true, true, true))

// Тайминги
PARAMETER(TOTALLY_LAUNCHED_AT, MINUTES_TO_MILLIS(60))
PARAMETER(TOTAL_LANDING_TIME,  MINUTES_TO_MILLIS(45) )

// Система состояний
PARAMETER(STATE_TIMER_TASK_MAX_COUNT, 15)
PARAMETER(STATE_SEQUENCE_MAX_SIZE, 30)

// Настройка пинов устройств SET_PIN(*смысловое имя пина/устройства*, *номер пина*)
SET_PIN(BUZZER, 6)
SET_PIN(LED_DATA, 35)
SET_PIN(THERMOREGULATOR, 20)
SET_PIN(LOG_THERMISTOR, 2)
SET_PIN(THERMOREGULATION_THERMISTOR, 0)
SET_PIN(GPS_RX, 4)
SET_PIN(GPS_TX, 3)

#endif  // CONFIG_H