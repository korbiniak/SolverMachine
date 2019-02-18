#include "include/solve.h"

int main(int argc, char * argv[]) {
	uint8_t level = 6;
	if(argc > 1)
		level = atoi(argv[1]);
	Solve machine((argc > 1), level);
	Cube cube(0);
	while(true) {
		cube = Cube(0);
		int type;
		cin >> type;
		if(type == 0)
			break;
		if(type == 1) {
			getchar();	
			string s = cube.readAlgo();
			cube.processAlgo(s);
		}
		else {
			cube.giveCubeString();
		}
		cout << machine.findSolution(cube) << "\n";
	}
	return 0;
}