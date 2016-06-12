#ifndef KnightriderEffect_h
#define KnightriderEffect_h

enum Direction {
  Forward,
  Backward
};

enum Interpolation {
  Linear,
  Quadratic,
  Advance
};

class KnightriderEffect
{
public:
  // default constructor
  KnightriderEffect() : 
    numLEDs(25), effectLength(5), type(Interpolation::Linear) {};
    
  KnightriderEffect(int numLEDs, Interpolation type, int effectLength) : 
    numLEDs(numLEDs), type(type), effectLength(effectLength) {};

  void start();
  void setDirection(Direction newDirection);
  void setSpeed(int newSpeed); // millis per LED
  void setMultiplier(double newMultiplier);
  void setHeadDistance(int newHeadDistance);
  double getBrightness(int index) const;

  
private:
  const int numLEDs, effectLength;
  const Interpolation type;
  Direction direction = Direction::Forward;
  int headDistance = 10, // distance between two wave heads
    speed = 100; // millis per LED
  double multiplier = 1;
  bool running = false;
  unsigned long startMillis;
};

#endif
