#ifndef GEN_H
#define GEN_H

#include "cube.h"

/* This class is called only on the begining of the program 
it generates/read pruning table for A* algorithm. You just make an Gen object, use generate()
and it does its job*/

class Gen {
public:
	void generate(uint8_t level);
	Gen();
};

#endif