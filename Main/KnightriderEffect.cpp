#include <math.h>

#include "Arduino.h"
#include "KnightriderEffect.h"

void KnightriderEffect::start()
{
  this->startMillis = millis();
  this->running = true;
}

void KnightriderEffect::setDirection(Direction newDirection)
{
  this->direction = newDirection;
}

void KnightriderEffect::setSpeed(int newSpeed)
{
  this->speed = newSpeed;
}

void KnightriderEffect::setMultiplier(double newMultiplier)
{
  this->multiplier = newMultiplier;
}

void KnightriderEffect::setHeadDistance(int newHeadDistance)
{
  this->headDistance = newHeadDistance;
}

double KnightriderEffect::getBrightness(int index) const {
  double brightness = 0.05; // low brightness level for LEDs which are not part of the "wave"

  if (!this->running) {
    return brightness;
  }

  if (this->direction == Direction::Backward) { // backward
    index = this->numLEDs - index - 1;
  }

  double virtualIndex = (double)index;
  virtualIndex += (double)(millis() - this->startMillis) / (double)this->speed;
  virtualIndex = fmod(virtualIndex, (double)this->headDistance);
  
  switch(this->type) {
    case Interpolation::Linear:
      // index inside effect length
      if (virtualIndex < this->effectLength) {
        brightness = 1 - virtualIndex / (double)this->effectLength;
      }
      
      // index outside effect length leads to brightness 0.0
      break;
      
    case Interpolation::Quadratic:
      break;

    case Interpolation::Advance:
      break;
      
    default:
      break;
  }

  return brightness * this->multiplier;
}

