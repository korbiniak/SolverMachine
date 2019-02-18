#include "rubicsStepper.h"

rubicsStepper::rubicsStepper() {
	dirPin = 0;
	stepPin = 0;
	begun = false;
}

void rubicsStepper::begin(byte _dirPin, byte _stepPin, int _stepDelay) {
	dirPin = _dirPin;
	stepPin = _stepPin;
	pinMode(dirPin, OUTPUT);
	pinMode(stepPin, OUTPUT);
	stepDelay = _stepDelay;
	begun = true;
}

void rubicsStepper::setPins(byte _dirPin, byte _stepPin) {
	dirPin = _dirPin;
	stepPin = _stepPin;
}

bool rubicsStepper::checkIfBegun() {
	if(!begun) {
		Serial.println("You didnt use begin function on this stepper motor!");
		return false;
	}
	return true;
}

void rubicsStepper::makeStep() {
	// if(!rubicsStepper::checkIfBegun()) return;
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(stepDelay);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(stepDelay);
}

void rubicsStepper::rotate(double angle, bool dir) {
	if(!rubicsStepper::checkIfBegun()) return;
	digitalWrite(dirPin, dir);
	int steps = angle * 200 / 360;
	for(int i = 0 ; i < steps ; ++i)
		rubicsStepper::makeStep();
}

void rubicsStepper::rotate(int steps, bool dir) {
	if(!rubicsStepper::checkIfBegun()) return;
	digitalWrite(dirPin, dir);
	for(int i = 0 ; i < steps ; ++i)
		rubicsStepper::makeStep();	
}

void rubicsStepper::rotateFace(char rotation) {
	if(!rubicsStepper::checkIfBegun())	return;
	switch(rotation) {
		case ' ': 
			rubicsStepper::rotate(50, RIGHT);
			break;
		case '\'':
			rubicsStepper::rotate(50, LEFT);
			break;
		case '2':
			rubicsStepper::rotate(100, RIGHT);
			break;
		default:
			rubicsStepper::rotate(50, RIGHT);
			break;
	}
}
