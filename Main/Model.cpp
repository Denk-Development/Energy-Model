#ifndef ModelState_cpp
#define ModelState_cpp

#include "KnightriderStrip.cpp"

class ModelState {
public: 
	ModelState(uint32_t rgb, double intensity, int speed, Direction direction) : 
		rgb(rgb), intensity(intensity), speed(speed), direction(direction) {}
	uint32_t rgb;
	double intensity;
	int speed;
	Direction direction;
};

class Model : public KnightriderStrip {
public: 
	Model(ModelState * states, uint8_t numStates, uint16_t n, uint8_t p, uint32_t rgb, neoPixelType t, Interpolation type, int effectLength, int headDistance, int speed, int startTime = 0) : 
		KnightriderStrip(n, p, rgb, t, type, effectLength, headDistance, speed), 
		states(states), 
		numStates(numStates)
	{
		if (startTime != -1) {
			this->update(startTime);
		}
	}

	void update(int time) {
		if (time >= this->numStates) {
			#ifdef DEBUG
				Serial.println("Invalid time value passed");
			#endif
			return;
		}

		this->updateStripe(this->states[time]);
	} 

private: 
	ModelState *states;
	uint8_t numStates;

	void updateStripe(ModelState state) {
		this->setColor(state.rgb);
		this->setMultiplier(state.intensity);
		this->setSpeed(state.speed);
		this->setDirection(state.direction);
	}
};

#endif