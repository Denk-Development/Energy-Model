#ifndef KnightriderStrip_cpp
#define KnightriderStrip_cpp

#include <Adafruit_NeoPixel.h>
#include "KnightriderEffect.h"

class KnightriderStrip : public KnightriderEffect
{
public:
	KnightriderStrip(uint16_t n, uint8_t p, uint8_t r, uint8_t g, uint8_t b, neoPixelType t, Interpolation type, int effectLength, int headDistance, int speed)
	: KnightriderEffect(n, type, effectLength), r(r), g(g), b(b)
	{
		this->strip = Adafruit_NeoPixel(n, p, t);
		this->strip.begin();

		this->setHeadDistance(headDistance);
		this->setSpeed(speed);
	}

	void update()
	{
		for (int i = 0; i < this->numLEDs; i++) {
			double b = this->getBrightness(i); // brightness
	    this->strip.setPixelColor(i, this->r * b, this->g * b, this->b * b);
	  }
	  strip.show();
	}

	void setColor(uint8_t r, uint8_t g, uint8_t b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->update();
	}


private:
	Adafruit_NeoPixel strip;
	uint8_t r, g, b;
};

#endif