#ifndef CUBE_H
#define CUBE_H

#include "face.h"

/* Main class, it defines our cube. With this class it is waaay easier to execute our 
solving algorithm and manipulate with the cube */

class Cube {
	//Size_t operator for hash map, in this case unordered_map 
	friend struct HashStruct;
private:
	//Our cube consists of 6 faces
	Face faces[6];
		
	//We want to calculate Cube's hash if we want to compare it with another cube
	//If we did it before and made no moves, we don't have to do this again, that is
	//why we use this boolean
	bool wasCompared;

	//These are static const variables. We used them for programming convenience only.
	//They are constant for every cube. CornerRot helps us rotating corners of face we are
	//rotating. EdgeRot helps rotating edges of rotated face
	//pot[i] is 7^i % MOD, it is used in calculating cubes hash (more about hashing there:
	//https://cp-algorithms.com/string/string-hashing.html)
	//init() inits those variable in compiling process
	static const uint8_t cornerRot[4];
	static const uint8_t edgeRot[4];
	static const array<long long, 54> pot;
	static const array<long long, 54> init();

	//These are functions that rotates the cube. Letter describes face we rotate, Dir 
	//describes direction. ' ' rotates it clockwise, '\'' rotates it counter clockwise,
	//'2' rotates it 180 degrees 
	void R(const char dir = ' ');
	void L(const char dir = ' ');
	void U(const char dir = ' ');
	void B(const char dir = ' ');
	void D(const char dir = ' ');
	void F(const char dir = ' ');

	//Helps rotating particular face, also checks if the given rotation is legal
	void rotateFace(const uint8_t face, const char dir = ' ');

public:
	//variable used in A* algorithm, it is basivally a h() function
	int heuristic;
	
	//variable used in A* algorithm, counts number of moves we have already done
	int moves;

	//creates a cube and set moves to _moves, set the cube in solved state
	Cube(int _moves);

	//creates a copy of cube
	Cube(const Cube &cube);

	//creates a cube out of string s
	//more info how the cube is described using string in config.h 
	Cube(string s);

	//NOTE!!!! Note that this class has no constructor with no arguments!

	//prints the cube
	void draw();

	//swaps particular face's corners in given dir
	void rotateCorners(const uint8_t face, const char dir = ' ');

	//swaps particular face's edges in given dir
	void rotateEdges(const uint8_t face, const char dir = ' ');

	//process given algorithm
	//more info how does the format of this string looks like is in cube.cpp
	void processAlgo(string alg);

	//process given rotation
	//more info how does the format look like in the cube.cpp
	void processRotation(string rot);

	//converts cube to string
	//more info how the cube is described using string in config.h 
	string toString();

	//reads algorithm from the user
	string readAlgo();

	//used in A*, returns h() function
	int giveH();

	//used for comparison of the cubes, cube that has larger heuristic is larger
	bool operator<(const Cube &cube1) const;
	bool operator==(const Cube &cube1)const;

	void giveCubeString();

	//reverse given algorithm, returns reversed algo and number of moves
	pair<string, int> reversedAlgo(string algo);
};

//used for hashing the cube to unordered_map
struct HashStruct {
	size_t operator()(const Cube &cube) const;
};

#endif