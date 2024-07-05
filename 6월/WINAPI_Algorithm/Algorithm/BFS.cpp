#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

//BFS
//깊이우선탐색 (Breath First Search)
// 간선상 최소거리
//

vector<vector<bool>> adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph_AdjacentMartrix()
{
	adjacent = vector<vector<bool>>(11, vector<bool>(11, false));

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;
	adjacent[1][3] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][3] = true;
	adjacent[2][7] = true;

	adjacent[3][1] = true;
	adjacent[3][2] = true;
	adjacent[3][3] = true;

	adjacent[4][4] = true;
	adjacent[4][5] = true;

	adjacent[5][4] = true;
	adjacent[5][5] = true;
	adjacent[5][6] = true;

	adjacent[6][5] = true;
	adjacent[6][6] = true;

	adjacent[7][2] = true;
	adjacent[7][7] = true;

	adjacent[8][8] = true;

	adjacent[9][9] = true;
	adjacent[9][10] = true;

	adjacent[10][9] = true;
	adjacent[10][10] = true;
}

void BFSWithoutQ(int start) {
	int N = adjacent.size();
	discovered[start] = true;
	parent[start] = start;

	cout << start << " visited" << endl;

	vector<int> q;
	q.push_back(start);
	int pop = 0;

	while (true) {
		if (pop >= q.size())
			break;

		int here = q[pop];
		pop++;

		for (int there = 0; there < N; there++) {
			if (adjacent[here][there] == false)
				continue;
			if (discovered[there] == true)
				continue;

			q.push_back(there);
			cout << there << " discovered!" << endl;
			discovered[there] = true;
			parent[there] = here;
		}
	}
}

void BFS(int start) {
	int N = adjacent.size();
	discovered[start] = true;
	parent[start] = start;

	cout << start << " visited" << endl;

	queue<int> q;
	q.push(start);

	while (true) {
		if (q.empty() == true) break;

		int here = q.front();
		q.pop();

		for (int there = 0; there < N; there++) {
			if (adjacent[here][there] == false)
				continue;
			if (discovered[there] == true)
				continue;

			q.push(there);
			cout << there << " discovered!" << endl;
			discovered[there] = true;
			parent[there] = here;
		}
	}
}

int edgeCount(int start, int dest) {
	BFS(start);


	bool found = false;
	int edges = 0;
	int acent = dest;

	if (parent[dest] == -1) {
		edges = -1;
	}
	else {
		while (true) {
			if (found) break;

			acent = parent[acent];

			if (acent == start) {
				found = true;
			}
			edges++;
		}
	}

	return edges;
}

void BFS_ALL() {
	int N = adjacent.size();

	for (int i = 0; i < N; i++) {
		if (!discovered[i]) {
			cout << endl;
			BFS(i);
		}
	}
}

int main() {
	CreateGraph_AdjacentMartrix();

	int size = adjacent.size();
	discovered = vector<bool>(size, false);
	parent = vector<int>(size, -1);

	BFSWithoutQ(0);
	
	int edges = edgeCount(0, 9);
	cout << "0 부터 " << "9 까지 edge 수 : " << edges << endl;

	return 0;
}