#include "Indications.h"
#include "Arduino.h"

// Leds
struct LedData {
  bool state = false;
  bool colors[3];
  int delta = 0;
  int count = 0;
  unsigned long timer = 0;

  LedDate(){};
};

LedData indicationLeds[LED_COUNT] = {};
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_DATA_PIN);

// Buzzer
bool buzzerState = false;
int buzzerTone = 0, buzzerDelta = 0, buzzerCount = 0;
unsigned long buzzerTimer = 0;

void setupIndications() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void changeBuzzerIndication(int buzTone, unsigned long buzDelta, int buzCount) {
  buzzerTone = buzTone;
  buzzerDelta = buzDelta;
  buzzerCount = buzCount * 2 - 1;
  buzzerTimer = millis();
  buzzerState = true;
  tone(BUZZER_PIN, buzzerTone);
}

void changeLedIndication(int ledNumber, bool rgbCls[3], unsigned long rgbDelta, int rgbCount) {
  LedData& led = indicationLeds[ledNumber];
  led.colors[0] = rgbCls[0];
  led.colors[1] = rgbCls[1];
  led.colors[2] = rgbCls[2];
  led.delta = rgbDelta;
  led.count = rgbCount * 2 - 1;
  led.timer = millis();
  led.state = true;
  
  ledStrip.setPixelColor(ledNumber, 255 * rgbCls[0], 255 * rgbCls[1], 255 * rgbCls[2]);
}

void indicate() {
  indicateWithBuzzer();
  indicateWithLeds();
}

void indicateWithBuzzer() {
  if (millis() - buzzerTimer >= buzzerDelta && buzzerCount != 0 && buzzerDelta != 0) {
    if (!buzzerState)
      tone(BUZZER_PIN, buzzerTone);
    else
      noTone(BUZZER_PIN);
    buzzerTimer = millis();
    buzzerState = !buzzerState;
    if (buzzerCount > 0)
      buzzerCount--;
  }
}

void indicateWithLeds() {
  for (int i = 0; i < LED_COUNT; ++i) {
    LedData& led = indicationLeds[i];

    if (millis() - led.timer >= led.delta && led.count != 0 && led.delta != 0) {
      ledStrip.setPixelColor(i, 255 * (led.colors[0] && led.state),
                                255 * (led.colors[1] && led.state),
                                255 * (led.colors[2] && led.state));

      ledStrip.show();

      led.timer = millis();
      led.state = !led.state;
      if (led.count > 0)
        led.count--;
    }
  }
}