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
PARAMETER(NEEDED_THERMOREGULATOR_TEMP_C, 80.0)

PARAMETER(LOG_MAX_COLUMNS, 10);

// Задание массивов ARRAY(*имя массива*, *тип элементов массива*, *кол-во элементов*, DATA(*элементы через запятую*))
ARRAY(PID_COEFFICIENTS, float, 3, DATA(1, 2, 3))

// Настройка пинов устройств SET_PIN(*смысловое имя пина/устройства*, *номер пина*)
SET_PIN(BUZZER, 2)
SET_PIN(LED_DATA, 35)
SET_PIN(THERMOREGULATOR, 20)
SET_PIN(LOG_THERMISTOR, 0)
SET_PIN(THERMOREGULATION_THERMISTOR, 0)

#endif  // CONFIG_H