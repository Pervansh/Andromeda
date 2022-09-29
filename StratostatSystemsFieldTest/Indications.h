#include <stdint.h>
#ifndef INDICATIONS_H
#define INDICATIONS_H

#include "config.h"

#include <Adafruit_NeoPixel.h>

void setupIndications();

void changeBuzzerIndication(int buzTone, unsigned long buzDelta = 0, int buzCount = -1);
void changeLedIndication   (int ledNumber, uint8_t rgbCls[3], unsigned long rgbDelta = 0, int rgbCount = -1);

void indicate();
void indicateWithBuzzer();
void indicateWithLeds();

#endif  // INDICATIONS_H