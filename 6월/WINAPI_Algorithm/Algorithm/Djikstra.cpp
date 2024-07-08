#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

struct Vertex
{
	Vertex(){}
	Vertex(int vertexNum, int g) : _vertexNum(vertexNum), _g(g){}
	int _vertexNum = 0;
	int _g = 0;//가중치

	bool operator<(const Vertex& other)const {
		return _g < other._g;
	}
	bool operator>(const Vertex& other)const {
		return _g > other._g;
	}
};

vector<vector<int>> adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph_AdjacentMartrix()
{
	adjacent = vector<vector<int>>(7, vector<int>(7, -1));

	adjacent[0][0] = 0;
	adjacent[0][1] = 3;
	adjacent[0][2] = 2;
	adjacent[0][4] = 10;

	adjacent[1][0] = 3;
	adjacent[1][1] = 0;

	adjacent[2][0] = 2;
	adjacent[2][2] = 0;
	adjacent[2][3] = 7;
	adjacent[2][4] = 3;
	adjacent[2][5] = 5;

	adjacent[3][2] = 7;
	adjacent[3][3] = 0;

	adjacent[4][0] = 10;
	adjacent[4][4] = 0;
	adjacent[4][6] = 1;

	adjacent[5][2] = 5;
	adjacent[5][5] = 0;

	adjacent[6][4] = 1;
	adjacent[6][6] = 0;
}

void Djikstra(int start) {
	parent = vector<int>(adjacent.size(), -1);
	vector<int> best(adjacent.size(), INT_MAX);
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	Vertex startV = Vertex(0, 0);
	best[start] = 0;
	pq.push(startV);

	parent[start] = start;

	while (true)
	{
		if (pq.empty()) break;

		Vertex hereV = pq.top();
		pq.pop();

		//전에 발견한 곳이 더 좋은 경로였을 때
		if (best[hereV._vertexNum] < hereV._g) {
			cout << hereV._vertexNum << endl;
			cout << hereV._g << endl;
			cout << best[hereV._vertexNum] << endl;
			continue;
		}

		for (int there = 0; there < adjacent.size(); there++) {
			if (hereV._vertexNum == there) continue;

			if (adjacent[hereV._vertexNum][there] == -1) continue;

			//지금 나의 위치의 best값 + there까지의 간선의 길이
			int newCost = best[hereV._vertexNum] + adjacent[hereV._vertexNum][there];

			//이전에 발견한 곳의 best가 더 작으면 새걸 넣지 않음.
			if (newCost >= best[there])continue;

			Vertex thereV = Vertex(there, newCost);
			pq.push(thereV);
			best[there] = newCost;
			parent[there] = hereV._vertexNum;
		}
	}
	for (int i = 0; i < adjacent.size(); i++) {
		cout << i << "의 부모 : " << parent[i] << endl;
		cout << "0부터 " << i << "까지의 최소 cost : " << best[i] << endl;
	}
}

int main() {
	CreateGraph_AdjacentMartrix();
	Djikstra(0);

	

	return 0;
}