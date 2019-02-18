#ifndef FACE_H
#define FACE_H

#include "digit.h"

/* This class helps making rotations */

class Face {
	friend class Cube;
	//Size_t operator for hash map, in this case unordered_map 
	friend struct HashStruct;
private:

	//Rubic's cube is build out of 9 tiles
	Digit tile[9];
public:

	//Basic constructor, does nothing
	Face();

	//Constructir that set the whole face for colour setColor
	Face(Digit setColor);

	//Makes a copy of a face
	Face(const Face &f);

	//Swap given tiles
	void swapTiles(uint8_t tile1, uint8_t tile2);
	
	//Return true if faces have the same colours arangement
	bool operator==(const Face &face1)const;
};

#endif