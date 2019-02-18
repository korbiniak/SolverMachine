#include "solver.h"

byte stepPins[] = {12, 10, 8, 6, 4, 2};
byte dirPins[] = {13, 11, 9, 7, 5, 3};
int stepDelay = 800;
int moveDelay = 10;
Solver solvingMachine;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  solvingMachine.begin(dirPins, stepPins, stepDelay, moveDelay);
}

void loop() {
  solvingMachine.processAlgo();
}
