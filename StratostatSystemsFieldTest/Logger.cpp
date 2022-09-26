#include "Logger.h"

#include <Arduino.h>
#include <SD.h>

Logger::Logger(const char* fileName = "data.txt") : FILE_NAME(fileName) {}

bool Logger::startLogging() {
  if (file) {
    return true;
  }

  if (SD.begin(SD_CARD)) {
    file = SD.open(FILE_NAME, FILE_WRITE);
    if (file) {
      // Писать заголовки
      file.println("'-\n");
      file.println("-# Time(s), Altitude(m), Velocity(m/s), Angles[x, y, z](grades), Servo[x, z](grades), State(num),,");
    } else {
      Serial.println("ERROR: SD-CARD CAN'T OPEN FILE");
    }
    loggingStartTimer = millis();
    return file;
  }
  Serial.println("ERROR: SD-CARD ISN'T OPEN");
  return false;
}

void Logger::finishLogging() {
  file.close();
}

void Logger::log() {

}

void Logger::logOnTimer() {

}

void Logger::setLoggingDelta(unsigned long newDelta){ 
  loggingDelta = newDelta;
}

Logger::~Logger() {
  finishLogging();
}