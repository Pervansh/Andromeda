#ifndef FOR_CONFIG_H
#define FOR_CONFIG_H

#include <Arduino.h>
#include <SD.h>
#include <GyverPID.h>

/*
  !!!НИЧЕГО ЗДЕСЬ НЕ ТРОГАТЬ!!!
  Вспомогательный файл для конфига
*/

// Для компилирования в Arduino IDE 2.0
#ifndef BUILTIN_SDCARD
  #define BUILTIN_SDCARD 10
#endif

#define PARAMETER(name, value)         constexpr auto name = value;
#define ARRAY(name, type, count, data) constexpr type name[ count ] = { data }; constexpr uint8_t name##_SIZE = count;
#define ARRAY_SIZE(name)               name##_SIZE
#define COUNT_FOR(counter,   array)    for (uint8_t counter = 0; counter < ARRAY_SIZE(array); ++counter)
// #define IN_RANGE (reference, array)    for ()
#define DATA(...)                      __VA_ARGS__
#define SET_PIN(name, pinNumber)       constexpr uint8_t name##_PIN = pinNumber;

#endif  // FOR_CONFIG_H