#include "include/face.h"

Face::Face() {}

Face::Face(Digit setColor) { 
	for(int i = 0 ; i < 9 ; ++i)
		tile[i] = setColor;
}

Face::Face(const Face &f) {
	for(int i = 0 ; i < 9 ; ++i)
		tile[i] = f.tile[i];
}	

void Face::swapTiles(uint8_t tile1, uint8_t tile2) {
	swap(tile[tile1], tile[tile2]);
}	

bool Face::operator==(const Face &face1)const {
	for(int i = 0 ; i < 9 ; ++i) 
		if(!(face1.tile[i] == tile[i]))
			return false;
	return true;
}