#include "solver.h"

Solver::Solver() {}

void Solver::begin(byte dirPins[6], byte stepPins[6], int stepDelay, int _moveDelay) {
	for(int i = 0 ; i < 6 ; ++i) {
		Serial.print("Begining stepper: ");
		Serial.print(i);
		Serial.print(" ");
		Serial.print(dirPins[i]);
		Serial.print(" ");
		Serial.print(stepPins[i]);
		Serial.println();
		Steppers[i].begin(dirPins[i], stepPins[i], stepDelay);
	}
	moveDelay = _moveDelay;
}

void Solver::rotateFace(byte face, char dir) {
	Steppers[face].rotateFace(dir);
	delay(moveDelay);
}

String Solver::readAlgo() {
	return Serial.readString();
}

void Solver::processRotation(String rot) {
	byte face;
	while(rot.length() > 0 && rot[0] == ' ')
		rot = rot.substring(1);
	if(rot.length() == 0) {
		Serial.println("Nie ma co obracac!");
		return;
	}
	char dir;
	switch(rot[0]) {
		case 'R': 
			face = RF;
			break;
		case 'L': 
			face = LF;
			break;
		case 'F': 
			face = FF;
			break;
		case 'D': 
			face = DF;
			break;
		case 'B': 
			face = BF;
			break;
		case 'U': 
			face = UF;
			break;
		default:
			Serial.println("Cos nie tak! Chcesz obrocic nieznana sciane.");
			return;
	}
	if(rot.length() == 1)
		dir = ' ';
	else dir = rot[1];

	// Serial.print("Obrot: ");
 	// Serial.print(rot[0]);
 	// Serial.println(dir);
	rotateFace(face, dir);
}

void Solver::processAlgo() {
	while(Serial.available() == 0) {}
	String algo = readAlgo();
	// Serial.println();
	// Serial.println(algo);
	String rot = "";
	for(unsigned int i = 0 ; i < algo.length() ; ++i) {
		if(algo[i] == ' ') {
			if(rot.length() > 0)
				processRotation(rot);
			rot = "";
		}
		else rot.concat(algo[i]);
	}
	processRotation(rot);
}
