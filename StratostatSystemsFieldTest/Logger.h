#pragma once

#include <SD.h>

class Logger {
private:
  File file;
  unsigned long logTimer;
  unsigned long loggingStartTimer;
  unsigned long loggingDelta;

public:
  const char* FILE_NAME;

  Logger(const char* fileName = "data.txt");

  bool startLogging();
  void finishLogging();

  void log();
  void logOnTimer();

  void setLoggingDelta(unsigned long newDelta);

  ~Logger();
};