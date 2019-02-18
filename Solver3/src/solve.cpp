#include "include/solve.h"

Solve::Solve(bool generate, uint8_t level) {
	if(generate == true) {
		Gen generuj;
		generuj.generate(level);
	}
	ifstream prunTxt("lib/pruningTable.txt");
	string line;
	if(prunTxt.is_open()) {	
		cout << "Opening pruning table file...\n";
		while(getline(prunTxt, line)) {
			if(line.size() >= 54)
				pruningTable[line.substr(0, 54)] = line.substr(54);
		}
	}else {
		cout << "Unable to open the pruning table file.\n";
	}
	cout << "Ready\n";
}

Solve::~Solve() {
	pruningTable.clear();
	vis.clear();
	while(!Q.empty())
		Q.pop();
}

string Solve::findSolution(Cube curCube) {
	string res = "";
	cout << "Finding solution for cube:\n";
	curCube.draw();
	
	vis.clear();
	while(!Q.empty())
		Q.pop();

	curCube.moves = 0;
	curCube.giveH();
	Q.push(curCube);
	vis[curCube] = "";

	int cnt = 0;
	cout << "H: " << curCube.giveH() << "\n";
	bool found = false;
	while(!found) {
		++cnt;
		curCube = Q.top();
		Q.pop();
		if(curCube.moves > MAX_MOVES)
			continue;

		string curRot = vis[curCube];	
		vector<Cube> v;
		v.clear();
		
		for(int i = 0 ; i < MOVES_CNT ; ++i) {
			Cube newCube(curCube);
			newCube.processRotation(moves[i]);
			if(vis.count(newCube) == 0) {
				v.push_back(newCube);
				vis[newCube] = curRot + " " + moves[i];
				if(pruningTable.count(newCube.toString()) > 0) {
					auto rev = newCube.reversedAlgo(pruningTable[newCube.toString()]);
					cout << "Found!\nMoves: " << newCube.moves + rev.second << "\n";
					res = vis[newCube] + " " + rev.first;
					found = true;
					break;
				}		
			}
		}
		sort(v.begin(), v.end());
		for(int i = v.size() - 1 ; i > v.size() / 2 ; --i)
			Q.push(v[i]);
	}
	return res;
}