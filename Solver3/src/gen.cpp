#include "include/gen.h"

Gen::Gen() {}

void Gen::generate(uint8_t level) {
	if(level > 6) {
		cout << "Pruning table will be too big, 6 is maximum.";
		return;
	}
	cout << "Generating..." << "\n";
	queue<pair<pair<Cube, string>, uint8_t>> q;
	unordered_map<Cube, bool, HashStruct> vis;
	Cube cube((int)0);

	ofstream pruningTableFile("lib/pruningTable.txt");

	q.push({{cube, ""}, 0});
	vis[cube] = true;

	int prev = 0;
	int cnt = 0;
	while(!q.empty()) {
		++cnt;

		Cube curCube = q.front().first.first;
		string curMoves = q.front().first.second;
		int movesCnt = q.front().second;
		q.pop();
		
		if(prev != movesCnt) {
			cout << cnt - 1 << " states ready: " << prev << " levels\n";
			prev = movesCnt;
		}

		pruningTableFile << curCube.toString() << curMoves << "\n";
		
		if(movesCnt < level) {
			Cube newCube(0);
			for(int i = 0 ; i < MOVES_CNT ; ++i) {
				newCube = curCube;
				newCube.processRotation(moves[i]);
				if(vis[newCube] == false) {
					q.push({{newCube, curMoves + " " + moves[i]}, movesCnt + 1});
					vis[newCube] = true;
				}
			}
		}
	}
	pruningTableFile << "}\n";
	cout << cnt << " states ready: " << prev << " levels\n";
	pruningTableFile.close();
	vis.clear();
	cout << "Ready\n";
}