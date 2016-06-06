#include <Adafruit_NeoPixel.h>

const int stripPin = 6, numLEDs = 25;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, stripPin, NEO_GRB + NEO_KHZ800);

class KnightriderEffectHelper
{
public:
  static double transferFunction(double x);
  
  KnightriderEffectHelper();
  KnightriderEffectHelper(int numLEDs, int effectLength);

  void start(int startLED, long millisPerStep, bool continuous, bool directionInverted = false);
  void jumpTo(int newStartLED);

  double getLEDIntensity(int index);

private:
  int numLEDs, effectLength, startLED;
  bool continuous,
    directionInverted; // false is default and means positive direction (0, 1, ...)
  long startMillis, // Arduino's millis() function
    millisPerStep; // speed
};

KnightriderEffectHelper::KnightriderEffectHelper() : numLEDs(100), effectLength(10) { }

KnightriderEffectHelper::KnightriderEffectHelper(int numLEDs, int effectLength) : 
  numLEDs(numLEDs), 
  effectLength(effectLength),
  continuous(continuous)
{
  
}

void KnightriderEffectHelper::start(int startLED, long millisPerStep, bool continuous, bool directionInverted)
{
  this->startLED = startLED;
  this->directionInverted = directionInverted;
  this->millisPerStep = millisPerStep;
  this->continuous = continuous;

  this->startMillis = millis();
}

double KnightriderEffectHelper::getLEDIntensity(int index)
{
  int runSoFar = (millis() - this->startMillis) / this->millisPerStep; // numer of LED which the effect has passed already

  if (this->continuous) {
    runSoFar %= this->numLEDs;
  }
  
  int head = (this->directionInverted) ? this->startLED - runSoFar : this->startLED + runSoFar;
  
  int offsetFromHead = (this->directionInverted) ? - head + index : head - index;
  
  if (offsetFromHead > 0) {
    if (offsetFromHead > this->effectLength) {
      return 0.0;
    }

    double rawIntensity = 1 - (double)offsetFromHead / (double)this->effectLength;
    return KnightriderEffectHelper::transferFunction(rawIntensity);
  }
  else if (offsetFromHead == 0) {
    return 1.0;
  }
  else {
    return 0.0;
  }
}

void  KnightriderEffectHelper::jumpTo(int newStartLED) 
{ 
  this->startLED = newStartLED;
}

double KnightriderEffectHelper::transferFunction(double x)
{
  x *= .666666;
  return x * x;
}

KnightriderEffectHelper knightriderEffect(numLEDs, 10);

void setup() 
{
  Serial.begin(9600);
  
  strip.begin();
  strip.show();
  
  knightriderEffect.start(0, 40, true);
}

void loop() 
{
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, knightriderEffect.getLEDIntensity(i) * (double)255));
  }
  strip.show();
}
