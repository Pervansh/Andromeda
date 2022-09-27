#include "Logger.h"

#include <Arduino.h>
#include <SD.h>
#include "config.h"

Logger::ObserverBase::ObserverBase(const String& _observationName)
  : observationName(_observationName) {}

const String& Logger::ObserverBase::getObservationName() {
  return observationName;
}

Logger::Logger(unsigned long _loggingDelay)
  : loggingDelay(_loggingDelay), observersCount(0) {}

bool Logger::startLogging(const char* fileName) {
  if (file) {
    return true;
  }

  if (SD.begin(SD_CARD_CHIP_SELECT)) {
    // Хз, работает чи нет
    file = SD.open(fileName, FILE_WRITE);

    if (file) {
      // Printing of column names
      file.print("Log time (millisecs), ");

      for (int i = 0; i < observersCount; ++i) {
        file.print(observers[i]->getObservationName());
        if (i < observersCount - 1) {
          file.print(", ");
        }
      }

      file.println();

    } else {
      Serial.println("ERROR: SD-CARD CAN'T OPEN THE FILE!");
    }

    loggingStartTimer = millis();
    return file;
  }
  
  Serial.println("ERROR: SD-CARD CAN'T BE OPENED!");
  return false;
}

bool Logger::startLogging(const String& fileName) {
  char* fileNameArray = new char[fileName.length()];
  fileName.toCharArray(fileNameArray, fileName.length() + 1);
  startLogging(fileNameArray);
  delete[] fileNameArray;
}

void Logger::finishLogging() {
  file.close();
}

void Logger::log() {
  if (file) {
    file.print(String(millis() - loggingStartTimer) + String(", "));

    for (int i = 0; i < observersCount; ++i) {
      file.print(observers[i]->observe());
      if (i < observersCount - 1) {
        file.print(", ");
      }
    }

    file.println();
  }
}

void Logger::logOnTimer() {
  if (millis() - logTimer >= loggingDelay && file) {
    logTimer = millis();
    log();
  }
}

void Logger::setLoggingDelay(unsigned long newDelay){ 
  loggingDelay = newDelay;
}

Logger::~Logger() {
  finishLogging();

  for (int i = 0; i < observersCount; ++i) {
    delete observers[i];
  }
}