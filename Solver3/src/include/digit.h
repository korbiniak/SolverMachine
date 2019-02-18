#ifndef DIGITS_H
#define DIGITS_H

#include "config.h"

/* This class is basically one rubic's cube tile, it will be easier to
manipulate with it later if done like that */

class Digit {
	//Size_t operator for hash map, in this case unordered_map 
	friend struct HashStruct;
private:
	//number from 0 to 5, defines tile's colour
	uint8_t digit;
public: 
	//Basic constructor, sets tile's color for WHITE
	Digit();

	//Constructor that sets Digit for another Digit's colour
	Digit(const Digit &d);

	//Constructor that sets Digit for d colour
	Digit(int d);

	//If 2 digits have the same colour it returns true, otherwise return false
	bool operator == (const Digit &d) const;  

	//Prints out tile's colour (If you run on Linux it will be coloured)
	void debug();

	//Returns Digit as char
	char giveChar();

	//Changes the colour for c
	void setColor(char c);
};

#endif