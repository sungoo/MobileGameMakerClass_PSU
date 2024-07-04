#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

//DFS
//깊이우선탐색 (Deep First Search)
// 재귀함수로 구현할 수 있음.(호출스택)
// 그래프가 모두 연결되어있는지 (=닫힌 계 인지) 확인하는 용도
//

vector<bool> visited;
vector<vector<bool>> adjacent;

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

int numNetwork = 1;

void DFS(int here) 
{
	cout << here << " visited" << endl;
	visited[here] = true;

	for (int there = 0; there < adjacent[here].size(); there++) {
		//here에서 there가 인접한 정점인지
		if (adjacent[here][there] == false) 
			continue;
	
		//there가 이미 방문한 곳인지
		if (visited[there] == true)
			continue;

		DFS(there);
	}
	for (int there = 0; there < visited.size(); there++) {
		if (!visited[there]) {
			//DFS를 다 돌았는데도 방문하지 않은 곳 == 열린 그래프
			cout << endl;
			numNetwork++;
			DFS(there);
		}
	}
}

int main() {
	CreateGraph_AdjacentMartrix();

	visited = vector<bool>(adjacent.size(), false);

	DFS(0);

	cout << "Number of Network : " << numNetwork << endl;

	return 0;
}