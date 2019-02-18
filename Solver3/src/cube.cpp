#include "include/cube.h"

const uint8_t Cube::edgeRot[4] = {1, 5, 7, 3};
const uint8_t Cube::cornerRot[4] = {0, 2, 8, 6};

const array<long long, 54> Cube::init() {
	array<long long, 54> temp; 
	long long base = 7;
	long long MOD = 1e9 + 7;
	temp[0] = 1LL;
	for(int i = 1 ; i < 54 ; ++i) {
		temp[i] = ((temp[i - 1] * base) % MOD);
	}
	return temp;
}

const array<long long, 54> Cube::pot = Cube::init();

Cube::Cube(int _moves) {
	heuristic = 72-_moves;
	moves = _moves;
	wasCompared = false;
	faces[WHITE] = Face(Digit(WHITE));
	faces[ORANGE] = Face(Digit(ORANGE));
	faces[GREEN] = Face(Digit(GREEN));
	faces[RED] = Face(Digit(RED));
	faces[BLUE] = Face(Digit(BLUE));
	faces[YELLOW] = Face(Digit(YELLOW));
}

Cube::Cube(const Cube &cube) {
	for(int i = 0 ; i < 6 ; ++i) 
		faces[i] = cube.faces[i];
	moves = cube.moves;
	heuristic = cube.heuristic;
}

Cube::Cube(string s) {
	for(int i = 0 ; i < 6 ; ++i) 
		for(int j = 0 ; j < 9 ; ++j)
			faces[i].tile[j].setColor(s[i * 9 + j]);			
}

void Cube::draw() {
	for(int i = 0 ; i < 3 ; ++i) {
		cout << "      ";	
		for(int j = 0 ; j < 3 ; ++j) {
			faces[UP].tile[(i * 3) + j].debug();
			cout << " ";
		}
		cout << "\n";
	}
	for(int i = 0 ; i < 3 ; ++i) {
		for(int h = LEFT ; h <= BACK ; ++h) 
			for(int j = 0 ; j < 3 ; ++j) {
				faces[h].tile[(i * 3) + j].debug();
				cout << " ";
			}
		cout << "\n";
	}
	for(int i = 0 ; i < 3 ; ++i) {
		cout << "      ";	
		for(int j = 0 ; j < 3 ; ++j) {
			faces[DOWN].tile[(i * 3) + j].debug();
			cout << " ";
		}
		cout << "\n";
	}
}

void Cube::rotateCorners(const uint8_t face, const char dir) {
	switch(dir) {
		case ' ': {
			Digit TEMP = faces[face].tile[cornerRot[3]];
			for(int i = 3 ; i > 0; --i) {
				faces[face].tile[cornerRot[i]] = faces[face].tile[cornerRot[i - 1]]; 
			}
			faces[face].tile[cornerRot[0]] = TEMP;
			break;	
		}
		case '\'': {
			Digit TEMP = faces[face].tile[cornerRot[0]];
			for(int i = 0 ; i < 3 ; ++i) {
				faces[face].tile[cornerRot[i]] = faces[face].tile[cornerRot[i + 1]]; 
			}
			faces[face].tile[cornerRot[3]] = TEMP;
			break;
		}
		case '2': {
			faces[face].swapTiles(0, 8);
			faces[face].swapTiles(2, 6);
			break;
		}
	}
}

void Cube::rotateEdges(const uint8_t face, const char dir) {
	switch(dir) {
		case ' ': {
			Digit TEMP = faces[face].tile[edgeRot[3]];
			for(int i = 3 ; i > 0; --i) {
				faces[face].tile[edgeRot[i]] = faces[face].tile[edgeRot[i - 1]]; 
			}
			faces[face].tile[edgeRot[0]] = TEMP;
			break;
		}
		case '\'': {
			Digit TEMP = faces[face].tile[edgeRot[0]];
			for(int i = 0 ; i < 3 ; ++i) {
				faces[face].tile[edgeRot[i]] = faces[face].tile[edgeRot[i + 1]]; 
			}
			faces[face].tile[edgeRot[3]] = TEMP;
			break;
		}
		case '2': {
			faces[face].swapTiles(1, 7);
			faces[face].swapTiles(3, 5);
			break;
		}
	}
}

void Cube::R(const char dir) {
	rotateEdges(RIGHT, dir);
	rotateCorners(RIGHT, dir);
	switch(dir) {
		case ' ': {
			Digit TEMP[3];
			for(int i = 0 , j = 2; i < 3 ; ++i, j += 3)
				TEMP[i] = faces[DOWN].tile[j];
			faces[DOWN].tile[2] = faces[BACK].tile[6];
			faces[DOWN].tile[5] = faces[BACK].tile[3];
			faces[DOWN].tile[8] = faces[BACK].tile[0];

			faces[BACK].tile[0] = faces[UP].tile[8];
			faces[BACK].tile[3] = faces[UP].tile[5];
			faces[BACK].tile[6] = faces[UP].tile[2];
			
			faces[UP].tile[2] = faces[FRONT].tile[2];
			faces[UP].tile[5] = faces[FRONT].tile[5];
			faces[UP].tile[8] = faces[FRONT].tile[8];
			
			faces[FRONT].tile[2] = TEMP[0];
			faces[FRONT].tile[5] = TEMP[1];
			faces[FRONT].tile[8] = TEMP[2];

			break;
		}
		case '\'': {
			Digit TEMP[3];
			for(int i = 0 , j = 2; i < 3 ; ++i, j += 3)
				TEMP[i] = faces[DOWN].tile[j];

			faces[DOWN].tile[2] = faces[FRONT].tile[2];
			faces[DOWN].tile[5] = faces[FRONT].tile[5];
			faces[DOWN].tile[8] = faces[FRONT].tile[8];

			faces[FRONT].tile[8] = faces[UP].tile[8];
			faces[FRONT].tile[5] = faces[UP].tile[5];
			faces[FRONT].tile[2] = faces[UP].tile[2];
			
			faces[UP].tile[2] = faces[BACK].tile[6];
			faces[UP].tile[5] = faces[BACK].tile[3];
			faces[UP].tile[8] = faces[BACK].tile[0];
			
			faces[BACK].tile[6] = TEMP[0];
			faces[BACK].tile[3] = TEMP[1];
			faces[BACK].tile[0] = TEMP[2];

			break;
		}
		case '2': {
			swap(faces[UP].tile[8], faces[DOWN].tile[8]);
			swap(faces[UP].tile[5], faces[DOWN].tile[5]);
			swap(faces[UP].tile[2], faces[DOWN].tile[2]);
			
			swap(faces[BACK].tile[0], faces[FRONT].tile[8]);
			swap(faces[BACK].tile[3], faces[FRONT].tile[5]);
			swap(faces[BACK].tile[6], faces[FRONT].tile[2]);	
		
			break;
		}
	}
}

void Cube::L(const char dir) {
	rotateEdges(LEFT, dir);
	rotateCorners(LEFT, dir);
	switch(dir) {
		case ' ': {
			Digit TEMP[3];
			for(int i = 0 , j = 0 ; i < 3 ; ++i, j += 3)
				TEMP[i] = faces[DOWN].tile[j];

			faces[DOWN].tile[0] = faces[FRONT].tile[0];
			faces[DOWN].tile[3] = faces[FRONT].tile[3];
			faces[DOWN].tile[6] = faces[FRONT].tile[6];

			faces[FRONT].tile[0] = faces[UP].tile[0];
			faces[FRONT].tile[3] = faces[UP].tile[3];
			faces[FRONT].tile[6] = faces[UP].tile[6];
			
			faces[UP].tile[0] = faces[BACK].tile[8];
			faces[UP].tile[3] = faces[BACK].tile[5];
			faces[UP].tile[6] = faces[BACK].tile[2];
			
			faces[BACK].tile[8] = TEMP[0];
			faces[BACK].tile[5] = TEMP[1];
			faces[BACK].tile[2] = TEMP[2];

			break;
		}
		case '\'': {
			Digit TEMP[3];
			for(int i = 0 , j = 0 ; i < 3 ; ++i, j += 3)
				TEMP[i] = faces[DOWN].tile[j];

			faces[DOWN].tile[0] = faces[BACK].tile[8];
			faces[DOWN].tile[3] = faces[BACK].tile[5];
			faces[DOWN].tile[6] = faces[BACK].tile[2];

			faces[BACK].tile[8] = faces[UP].tile[0];
			faces[BACK].tile[5] = faces[UP].tile[3];
			faces[BACK].tile[2] = faces[UP].tile[6];
			
			faces[UP].tile[0] = faces[FRONT].tile[0];
			faces[UP].tile[3] = faces[FRONT].tile[3];
			faces[UP].tile[6] = faces[FRONT].tile[6];
			
			faces[FRONT].tile[0] = TEMP[0];
			faces[FRONT].tile[3] = TEMP[1];
			faces[FRONT].tile[6] = TEMP[2];

			break;
		}
		case '2': {
			swap(faces[UP].tile[0], faces[DOWN].tile[0]);
			swap(faces[UP].tile[3], faces[DOWN].tile[3]);
			swap(faces[UP].tile[6], faces[DOWN].tile[6]);
			
			swap(faces[BACK].tile[2], faces[FRONT].tile[6]);
			swap(faces[BACK].tile[5], faces[FRONT].tile[3]);
			swap(faces[BACK].tile[8], faces[FRONT].tile[0]);
		
			break;
		}
	}
}

void Cube::U(const char dir) {
	rotateEdges(UP, dir);
	rotateCorners(UP, dir);
	switch(dir) {
		case ' ': {
			Digit TEMP[3];
			for(int i = 0 ; i < 3 ; ++i)
				TEMP[i] = faces[FRONT].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[FRONT].tile[i] = faces[RIGHT].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[RIGHT].tile[i] = faces[BACK].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[BACK].tile[i] = faces[LEFT].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[LEFT].tile[i] = TEMP[i];

			break;
		}
		case '\'': {
			Digit TEMP[3];
			for(int i = 0 ; i < 3 ; ++i)
				TEMP[i] = faces[FRONT].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[FRONT].tile[i] = faces[LEFT].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[LEFT].tile[i] = faces[BACK].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[BACK].tile[i] = faces[RIGHT].tile[i];
			
			for(int i = 0 ; i < 3 ; ++i)
				faces[RIGHT].tile[i] = TEMP[i];

			break;
		}
		case '2': {
			for(int i = 0 ; i < 3 ; ++i)			
				swap(faces[RIGHT].tile[i], faces[LEFT].tile[i]);

			for(int i = 0 ; i < 3 ; ++i)
				swap(faces[BACK].tile[i], faces[FRONT].tile[i]);
		
			break;
		}
	}
}

void Cube::D(const char dir) {
	rotateEdges(DOWN, dir);
	rotateCorners(DOWN, dir);
	switch(dir) {
		case ' ': {
			Digit TEMP[3];
			for(int i = 6 ; i < 9 ; ++i)
				TEMP[i - 6] = faces[FRONT].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[FRONT].tile[i] = faces[LEFT].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[LEFT].tile[i] = faces[BACK].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[BACK].tile[i] = faces[RIGHT].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[RIGHT].tile[i] = TEMP[i - 6];

			break;
			
		}
		case '\'': {
			Digit TEMP[3];
			for(int i = 6 ; i < 9 ; ++i)
				TEMP[i - 6] = faces[FRONT].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[FRONT].tile[i] = faces[RIGHT].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[RIGHT].tile[i] = faces[BACK].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[BACK].tile[i] = faces[LEFT].tile[i];
			
			for(int i = 6 ; i < 9 ; ++i)
				faces[LEFT].tile[i] = TEMP[i - 6];

			break;
		}
		case '2': {
			for(int i = 6 ; i < 9 ; ++i)	
				swap(faces[RIGHT].tile[i], faces[LEFT].tile[i]);

			for(int i = 6 ; i < 9 ; ++i)
				swap(faces[BACK].tile[i], faces[FRONT].tile[i]);
		
			break;
		}
	}
}

void Cube::F(const char dir) {
	rotateEdges(FRONT, dir);
	rotateCorners(FRONT, dir);
	switch(dir) {
		case ' ': {
			Digit TEMP[3];
			for(int i = 0 ; i < 3 ; ++i)
				TEMP[i] = faces[DOWN].tile[i];

			faces[DOWN].tile[0] = faces[RIGHT].tile[6];
			faces[DOWN].tile[1] = faces[RIGHT].tile[3];
			faces[DOWN].tile[2] = faces[RIGHT].tile[0];

			faces[RIGHT].tile[0] = faces[UP].tile[6];
			faces[RIGHT].tile[3] = faces[UP].tile[7];
			faces[RIGHT].tile[6] = faces[UP].tile[8];
			
			faces[UP].tile[6] = faces[LEFT].tile[8];
			faces[UP].tile[7] = faces[LEFT].tile[5];
			faces[UP].tile[8] = faces[LEFT].tile[2];
			
			faces[LEFT].tile[2] = TEMP[0];
			faces[LEFT].tile[5] = TEMP[1];
			faces[LEFT].tile[8] = TEMP[2];

			break;
		}
		case '\'': {
			Digit TEMP[3];
			for(int i = 0 ; i < 3 ; ++i)
				TEMP[i] = faces[DOWN].tile[i];

			faces[DOWN].tile[0] = faces[LEFT].tile[2];
			faces[DOWN].tile[1] = faces[LEFT].tile[5];
			faces[DOWN].tile[2] = faces[LEFT].tile[8];

			faces[LEFT].tile[8] = faces[UP].tile[6];
			faces[LEFT].tile[5] = faces[UP].tile[7];
			faces[LEFT].tile[2] = faces[UP].tile[8];
			
			faces[UP].tile[6] = faces[RIGHT].tile[0];
			faces[UP].tile[7] = faces[RIGHT].tile[3];
			faces[UP].tile[8] = faces[RIGHT].tile[6];
			
			faces[RIGHT].tile[6] = TEMP[0];
			faces[RIGHT].tile[3] = TEMP[1];
			faces[RIGHT].tile[0] = TEMP[2];

			break;
		}
		case '2': {
			swap(faces[UP].tile[6], faces[DOWN].tile[2]);
			swap(faces[UP].tile[7], faces[DOWN].tile[1]);
			swap(faces[UP].tile[8], faces[DOWN].tile[0]);
			
			swap(faces[LEFT].tile[2], faces[RIGHT].tile[6]);
			swap(faces[LEFT].tile[5], faces[RIGHT].tile[3]);
			swap(faces[LEFT].tile[8], faces[RIGHT].tile[0]);
		
			break;
		}
	}
}

void Cube::B(const char dir) {
	rotateEdges(BACK, dir);
	rotateCorners(BACK, dir);
	switch(dir) {
		case ' ': {
			Digit TEMP[3];
			for(int i = 0 ; i < 3 ; ++i)
				TEMP[i] = faces[DOWN].tile[i + 6];

			faces[DOWN].tile[6] = faces[LEFT].tile[0];
			faces[DOWN].tile[7] = faces[LEFT].tile[3];
			faces[DOWN].tile[8] = faces[LEFT].tile[6];

			faces[LEFT].tile[0] = faces[UP].tile[2];
			faces[LEFT].tile[3] = faces[UP].tile[1];
			faces[LEFT].tile[6] = faces[UP].tile[0];
			
			faces[UP].tile[2] = faces[RIGHT].tile[8];
			faces[UP].tile[1] = faces[RIGHT].tile[5];
			faces[UP].tile[0] = faces[RIGHT].tile[2];
			
			faces[RIGHT].tile[8] = TEMP[0];
			faces[RIGHT].tile[5] = TEMP[1];
			faces[RIGHT].tile[2] = TEMP[2];

			break;
		}
		case '\'': {
			Digit TEMP[3];
			for(int i = 0 ; i < 3 ; ++i)
				TEMP[i] = faces[DOWN].tile[i + 6];

			faces[DOWN].tile[6] = faces[RIGHT].tile[8];
			faces[DOWN].tile[7] = faces[RIGHT].tile[5];
			faces[DOWN].tile[8] = faces[RIGHT].tile[2];

			faces[RIGHT].tile[8] = faces[UP].tile[2];
			faces[RIGHT].tile[5] = faces[UP].tile[1];
			faces[RIGHT].tile[2] = faces[UP].tile[0];
			
			faces[UP].tile[2] = faces[LEFT].tile[0];
			faces[UP].tile[1] = faces[LEFT].tile[3];
			faces[UP].tile[0] = faces[LEFT].tile[6];
			
			faces[LEFT].tile[0] = TEMP[0];
			faces[LEFT].tile[3] = TEMP[1];
			faces[LEFT].tile[6] = TEMP[2];

			break;
		}
		case '2': {
			swap(faces[UP].tile[0], faces[DOWN].tile[8]);
			swap(faces[UP].tile[1], faces[DOWN].tile[7]);
			swap(faces[UP].tile[2], faces[DOWN].tile[6]);
			
			swap(faces[LEFT].tile[0], faces[RIGHT].tile[8]);
			swap(faces[LEFT].tile[3], faces[RIGHT].tile[5]);
			swap(faces[LEFT].tile[6], faces[RIGHT].tile[2]);
		
			break;
		}
	}
}	

void Cube::rotateFace(const uint8_t face, const char dir) {
	wasCompared = false;
	switch(face) {
		case RIGHT:
			R(dir);
			break;
		case LEFT:
			L(dir);
			break;
		case BACK:
			B(dir);
			break;
		case UP:
			U(dir);
			break;
		case FRONT:
			F(dir);
			break;
		case DOWN:
			D(dir);
			break;	
	}
	moves++;
}

void Cube::processRotation(string rot) {
	uint8_t face;
	while(rot.size() > 0 && rot[0] == ' ')
		rot = rot.substr(1);
	if(rot.size() == 0) {
		cout << "There is nothing to rotate!\n";
		return;
	}
	char dir;
	switch(rot[0]) {
		case 'R': 
			face = RIGHT;
			break;
		case 'L': 
			face = LEFT;
			break;
		case 'F': 
			face = FRONT;
			break;
		case 'D': 
			face = DOWN;
			break;
		case 'B': 
			face = BACK;
			break;
		case 'U': 
			face = UP;
			break;
		default:
			cout << "Something is wrong! You want to rotate face that does not exist!\n";
			return;
	}
	if(rot.size() == 1)
		dir = ' ';
	else dir = rot[1];
	// cout << "Obrot: " << rot[0] << dir << "\n";
	rotateFace(face, dir);
	giveH();
}

void Cube::processAlgo(string algo) {
	string rot = "";
	for(unsigned int i = 0 ; i < algo.length() ; ++i) {
		if(algo[i] == ' ') {
			if(rot.size() > 0)
				processRotation(rot);
			rot = "";
		}
		else rot.push_back(algo[i]);
	}
	processRotation(rot);
}

string Cube::readAlgo() {
	char c;
	string res;
	do {
		c = getchar();
		res.push_back(c);
	}while(c != '\n');
	res.pop_back();
	puts("");
	return res;
}

bool Cube::operator==(const Cube &cube1) const {
	for(int i = 0 ; i < 6 ; ++i)
		if(!(cube1.faces[i] == faces[i]))
			return false;
	return true;
}

int Cube::giveH() {
	heuristic = 0;
	for(int i = 0 ; i < 6 ; ++i) {
		if(faces[i].tile[0] == faces[i].tile[1]) heuristic++;
		if(faces[i].tile[1] == faces[i].tile[2]) heuristic++;
		if(faces[i].tile[3] == faces[i].tile[4]) heuristic++;
		if(faces[i].tile[4] == faces[i].tile[5]) heuristic++;
		if(faces[i].tile[6] == faces[i].tile[7]) heuristic++;
		if(faces[i].tile[7] == faces[i].tile[8]) heuristic++;
		if(faces[i].tile[0] == faces[i].tile[3]) heuristic++;
		if(faces[i].tile[1] == faces[i].tile[4]) heuristic++;
		if(faces[i].tile[2] == faces[i].tile[5]) heuristic++;
		if(faces[i].tile[3] == faces[i].tile[6]) heuristic++;
		if(faces[i].tile[4] == faces[i].tile[7]) heuristic++;
		if(faces[i].tile[5] == faces[i].tile[8]) heuristic++;
	}
	heuristic *= HEURISTIC_MULT;
	heuristic -= (moves * MOVES_MULTIPLIER);
	return heuristic;
}

bool Cube::operator<(const Cube &cube1)const{
	return heuristic < cube1.heuristic;
}

string Cube::toString() {
	string s;
	for(int i = 0 ; i < 6 ; ++i)
		for(int j = 0 ; j < 9 ; ++j)
			s.push_back(faces[i].tile[j].giveChar());
	return s;
}

pair<string, int> Cube::reversedAlgo(string algo) {
	string ans = "";
	string rot = "";
	int cnt = 0;
	while(algo.size() > 0 && algo.back()) {
		if(algo.back() == ' ' && rot.size() > 0) {
			if(rot[0] == '\'')	rot = rot[1];
			else if (rot.size() == 1) rot += '\'';
			else reverse(rot.begin(), rot.end());
			ans = ans + rot + " ";
			rot = "";		
			cnt++;
		}else rot.push_back(algo.back());
		algo.pop_back();
	}
	return {ans, cnt};
}

size_t HashStruct::operator()(const Cube &cube) const {
	long long hash = 0;
	long long MOD = 1e9 + 7;
	for(int i = 0 ; i < 6; ++i) 
		for(int j = 0 ; j < 9 ; ++j)
			hash += (cube.pot[i * 9 + j] * (long long)(cube.faces[i].tile[j].digit + 1)) % MOD;
	return (size_t)hash;		
}

void Cube::giveCubeString() {
	string s;
	cin >> s;
	map<char, char> col = {{'W', '0'}, {'O', '1'}, {'G', '2'}, {'R', '3'}, {'B', '4'}, {'Y', '5'}};
	for(int i = 0 ; i < 6 ; ++i) 
		for(int j = 0 ; j < 9 ; ++j) {
			faces[i].tile[j].setColor(col[s[i*9 + j]]);
		}
}