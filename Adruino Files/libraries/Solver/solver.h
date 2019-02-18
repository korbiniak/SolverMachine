#ifndef SOLVER_H
#define SOLVER_H

#include "config.h"
#include "rubicsStepper.h"

class Solver {
private:
	rubicsStepper Steppers[6];
	int moveDelay;
	String readAlgo();
public:
	Solver();
	void begin(byte dirPins[6], byte stepPins[6], int stepDelay = 1000, int _moveDelay = 1000);
	void processAlgo();
	void processRotation(String rot);
	void rotateFace(byte face, char dir);
};

#endif