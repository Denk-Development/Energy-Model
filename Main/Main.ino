#include "KnightriderStrip.cpp"

#include <Adafruit_NeoPixel.h>
#include "KnightriderEffect.h"

#define DEBUG

const int stripPin = 6, numLEDs = 25;

KnightriderStrip test(
  numLEDs, 
  stripPin, 
  255, 255, 0, // color
  NEO_GRB + NEO_KHZ800, 
  Interpolation::Linear, 
  5, // effect length
  10, // head distance
  80); // speed

unsigned long startMillis;

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("running...");
  #endif

  test.start();
}

void loop() {
  if (startMillis + 10000 < millis() % 20000) {
    test.setColor(255, 0, 0);
    test.setDirection(Direction::Backward);
    test.setMultiplier(1);
  }
  if (startMillis + 4000 < millis() % 20000) {
    test.setColor(255, 0, 255);
    test.setMultiplier(.1);
  }
  if (startMillis + 6000 < millis() % 20000) {
    test.setColor(0, 0, 255);
    test.setMultiplier(.5);
  }
  test.update();
}
