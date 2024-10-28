#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

//DFS
//���̿켱Ž�� (Deep First Search)
// ����Լ��� ������ �� ����.(ȣ�⽺��)
// �׷����� ��� ����Ǿ��ִ��� (=���� �� ����) Ȯ���ϴ� �뵵
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
		//here���� there�� ������ ��������
		if (adjacent[here][there] == false) 
			continue;
	
		//there�� �̹� �湮�� ������
		if (visited[there] == true)
			continue;

		DFS(there);
	}
	for (int there = 0; there < visited.size(); there++) {
		if (!visited[there]) {
			//DFS�� �� ���Ҵµ��� �湮���� ���� �� == ���� �׷���
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