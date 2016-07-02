#include "Model.cpp"

#include <Adafruit_NeoPixel.h>
#include "KnightriderEffect.h"

#define DEBUG

const int stripPin = 6, numLEDs = 25;

typedef uint32_t Color;

inline Color rgb(uint8_t r, uint8_t g, uint8_t b) {
  return Adafruit_NeoPixel::Color(r, g, b);
}

// colors
const Color cSun = rgb(255, 255, 100),
  cWind = rgb(255, 255, 255),
  cWaterPowerPumpedStorageHydroPowerStation = rgb(0, 0, 255),
  cPump = rgb(255, 0, 0),
  cGenerator = rgb(0, 255, 0),
  cThermicPowerStation = rgb(255, 50, 0),
  cWaterPower = rgb(72, 209, 204),
  cConsumer = rgb(153, 50, 204);

KnightriderStrip test(
  numLEDs, 
  stripPin, 
  cWaterPower, // color
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
  test.update();
}
