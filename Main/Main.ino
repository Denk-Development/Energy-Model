#include <Adafruit_NeoPixel.h>

#include "KnightriderEffect.h"

#define DEBUG

const int stripPin = 6, numLEDs = 25;

Adafruit_NeoPixel strip(numLEDs, stripPin, NEO_GRB + NEO_KHZ800);
KnightriderEffect stripEffect(numLEDs, Interpolation::Linear, 5);

unsigned long startMillis;

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("running...");
  #endif

  stripEffect.setHeadDistance(10);
  stripEffect.setSpeed(80);
  
  strip.begin();
  stripEffect.start();
  
  startMillis = millis();
}

void loop() {
  if (startMillis + 10000 < millis()) {
    stripEffect.setDirection(Direction::Backward);
  }
  for (int i = 0; i < numLEDs; i++) {
    strip.setPixelColor(i, 0, 0, stripEffect.getBrightness(i) * 255);
  }
  strip.show();
}
