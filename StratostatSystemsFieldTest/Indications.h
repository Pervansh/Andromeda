#ifndef INDICATIONS_H
#define INDICATIONS_H

#include "config.h"

#include <Adafruit_NeoPixel.h>

// Leds
struct LedData {
  bool state = false;
  bool colors[3];
  int delta = 0;
  int count = 0;
  unsigned long timer = 0;

  LedDate(){};
};

extern LedData indicationLeds[LED_COUNT];
extern Adafruit_NeoPixel ledStrip;

// Buzzer
extern bool buzzerState;
extern int buzzerTone, buzzerDelta, buzzerCount;
extern unsigned long buzzerTimer;

void setupIndications();

void changeBuzzerIndication(int buzTone, unsigned long buzDelta = 0, int buzCount = -1);
void changeLedIndication   (int ledNumber, bool rgbCls[3], unsigned long rgbDelta = 0, int rgbCount = -1);

void indicate();
void indicateWithBuzzer();
void indicateWithLeds();

#endif  // INDICATIONS_H