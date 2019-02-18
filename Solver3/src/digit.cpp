#include "include/digit.h"

Digit::Digit() {
	digit = 0;
}

Digit::Digit(const Digit &d) {
	digit = d.digit;
}

Digit::Digit(int d) {
	digit = (uint8_t)d;
}

bool Digit::operator == (const Digit &d) const {
	return digit == d.digit;
}

void Digit::debug() {
	if(digit == WHITE) 	cout << "W";
	if(digit == ORANGE)	cout << "\e[35mO\e[0m";
	if(digit == GREEN)	cout << "\e[32mG\e[0m";
	if(digit == RED)	cout << "\e[31mR\e[0m";
	if(digit == BLUE)	cout << "\e[34mB\e[0m";
	if(digit == YELLOW)	cout << "\e[33mY\e[0m";
}

char Digit::giveChar() {
	return (char)(digit + '0');
}

void Digit::setColor(char c) {
	digit = (uint8_t)(c - '0');
}