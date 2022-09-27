#pragma once

#include <SD.h>
#include <Arduino.h>
#include "config.h"

class Logger {
private:
  class ObserverBase {
  private:
    String observationName;

  public:
    ObserverBase(const String& _observationName);
    virtual String observe() = 0;
    const String& getObservationName();
  };

  // For FuncType use only FUNCTORS with convertable to String return values!
  template<typename FuncType>
  class Observer : public ObserverBase {
  private:
    FuncType interviewee;
  
  public:
    Observer(const String& _observationName, FuncType _interviewee);
    String observe() override;
  };

  File file;

  unsigned long logTimer;
  unsigned long loggingStartTimer;
  unsigned long loggingDelay;

  int observersCount;
  ObserverBase* observers[LOG_MAX_DATA_COLUMNS];

public:

  Logger(unsigned long _loggingDelay = 50);

  bool startLogging(const String& fileName = "data.txt");
  void finishLogging();

  void log();
  void logOnTimer();

  /*!
    @brief For FuncType use only FUNCTORS with convertable to String return values!
           Creates data column in log file. Every call of log() asks columnDataFunc for data
           and writes it in column.
           Doesn't create column if current data column count equals LOG_MAX_DATA_COLUMNS.
    @return true if column was created, false if otherwise.
  */
  template<typename FuncType>
  bool addColumn(const String& columnName, FuncType columnDataFunc);

  // Sets time delta for logOnTimer()
  void setLoggingDelay(unsigned long newDelay);

  ~Logger();
};

template<typename FuncType>
bool Logger::addColumn(const String& columnName, FuncType columnDataFunc) {
  // Можно добавить добавления заголовка столбца после startLogging()

  if (observersCount < LOG_MAX_DATA_COLUMNS) {
    observers[observersCount] = new Observer<FuncType>(columnName, columnDataFunc);
    observersCount++;
    return true;
  }

  return false;
}


// Logeer::Observer definitions

template<typename FuncType>
Logger::Observer<FuncType>::Observer(const String& _observationName, FuncType _interviewee)
  : Logger::ObserverBase(_observationName), interviewee(_interviewee) {}

template<typename FuncType>
String Logger::Observer<FuncType>::observe() {
  return String(interviewee());
}
