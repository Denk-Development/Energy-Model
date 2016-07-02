#ifndef KnightriderStrip_cpp
#define KnightriderStrip_cpp

#include <Adafruit_NeoPixel.h>
#include "KnightriderEffect.h"

class KnightriderStrip : public KnightriderEffect
{
public:
	KnightriderStrip(uint16_t n, uint8_t p, uint32_t rgb, neoPixelType t, Interpolation type, int effectLength, int headDistance, int speed)
	: KnightriderEffect(n, type, effectLength)
	{
		this->strip = Adafruit_NeoPixel(n, p, t);
		this->strip.begin();

		this->setHeadDistance(headDistance);
		this->setSpeed(speed);
		this->setColor(rgb);
	}

	void update()
	{
		for (int i = 0; i < this->numLEDs; i++) {
			double b = this->getBrightness(i); // brightness
	    this->strip.setPixelColor(i, this->r * b, this->g * b, this->b * b);
	  }
	  strip.show();
	}

	void setColor(uint32_t c)
	{
		this->r = (uint8_t)(c >> 16);
		this->g = (uint8_t)(c >>  8);
		this->b = (uint8_t)c;
		this->update();
	}


private:
	Adafruit_NeoPixel strip;
	uint8_t r, g, b;
};

#endif