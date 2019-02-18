#ifndef RUBICSSTEPER_H
#define RUBICSSTEPER_H

#include "config.h"

class rubicsStepper {
private:
	byte dirPin;
	byte stepPin;
	int stepDelay;
	bool begun;
	bool checkIfBegun();
public:
	rubicsStepper();
	void makeStep();
	void begin(byte _dirPin, byte _stepPin, int _stepDelay);
	void setPins(byte _dirPin, byte _stepPin);
	void rotate(double angle, bool dir);
	void rotate(int steps, bool dir);
	void rotateFace(char rotation);
};

#endif