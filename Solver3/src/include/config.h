#ifndef CONFIG_H
#define CONFIG_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <map>

using namespace std;

#define UP 0
#define	LEFT 1
#define	FRONT 2
#define RIGHT 3
#define	BACK 4
#define	DOWN 5

#define	WHITE 0
#define	ORANGE 1
#define	GREEN 2
#define	RED 3
#define BLUE 4
#define	YELLOW 5

#define MOVES_CNT 18
#define MAX_MOVES 20
#define MOVES_MULTIPLIER 3
#define HEURISTIC_MULT 2

const string moves[18] = {"R\'", "R", "R2", 
						"L", "L\'", "L2",
 						"U", "U\'", "U2", 
						"F", "F\'", "F2", 
						"D", "D\'", "D2", 
						"B", "B\'", "B2"};


#endif