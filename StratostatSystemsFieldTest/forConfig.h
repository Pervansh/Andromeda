#ifndef FOR_CONFIG_H
#define FOR_CONFIG_H

#include <Arduino.h>

/*
  !!!НИЧЕГО ЗДЕСЬ НЕ ТРОГАТЬ!!!
  Вспомогательный файл для конфига
*/

#define PARAMETER(name, value)         const auto name = value;
#define ARRAY(name, type, count, data) const type name[ count ] = { data };
#define DATA(...)                      __VA_ARGS__
#define SET_PIN(name, pinNumber)       const uint8_t name##_PIN = pinNumber;

#endif  // FOR_CONFIG_H