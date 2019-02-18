#ifndef SOLVE_H
#define SOLVE_H

#include "gen.h"

/* Main class of the program. It finds solution for the given cube */

class Solve {
private:
	//pruning table for A* algorithm
	unordered_map<string, string> pruningTable;

	//map of visited states. We don't want to process them again
	unordered_map<Cube, string, HashStruct> vis;	  

	//queue of the cubes, it gives us cube with the largest h() function
	priority_queue<Cube> Q;
public:

	//it constructs the machine. If generate == 0, then it reads pruning table from the 
	//previously made file. Otherwise it generates it. Level is the level of pruning. 6 is 
	//maximum
	Solve(bool generate, uint8_t level);
	~Solve();

	//Finds solution for given cube
	string findSolution(Cube curCube);
};

#endif