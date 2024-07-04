#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

//�׷���
// �����ϸ�Ʈ ���Ϸ� (�Ѻױ׸��⸦ ���� �׷��� �ڷᱸ�� ����)
//
// ����(Node, Vertex)�� ����(edge)���� �̷���� �ڷᱸ��
// 
// 1. ��������Ʈ
vector<vector<int>> adjacent_List;

void CreateGraph_AdjacentList() {
	adjacent_List = vector<vector<int>>(7, vector<int>());

	adjacent_List[0].push_back(1);
	adjacent_List[0].push_back(2);
	adjacent_List[0].push_back(4);

	adjacent_List[1].push_back(0);

	adjacent_List[2].push_back(0);
	adjacent_List[2].push_back(3);
	adjacent_List[2].push_back(5);

	adjacent_List[3].push_back(2);

	adjacent_List[4].push_back(0);
	adjacent_List[4].push_back(6);

	adjacent_List[5].push_back(2);

	adjacent_List[6].push_back(4);
}

// 2. ���� ���
vector<vector<bool>> adjacent;

void CreateGraph_AdjacentMartrix() {
	//     0  1  2  3  4  5  6
	// 0   T  T  T  F  T  F  F
	// 1   T  T  0  0  0  0  0
	// 2   . . .
	// 3
	// 4
	// 5
	// 6
	//

	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][4] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][3] = true;
	adjacent[2][5] = true;

	adjacent[3][2] = true;
	adjacent[3][3] = true;

	adjacent[4][0] = true;
	adjacent[4][4] = true;
	adjacent[4][6] = true;

	adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][4] = true;
	adjacent[6][6] = true;
}

int main() {
	CreateGraph_AdjacentList();
	CreateGraph_AdjacentMartrix();

	//0�� 2�� ������ ����Ǿ��ֳ�.
	bool isConnected = false;
	for (int i = 0; i < adjacent_List[0].size(); i++) {
		if (adjacent_List[0][i] == 2)
			isConnected = true;
	}

	if (isConnected)
		cout << "0�� 2�� ����Ǿ�����" << endl;

	//5�� 4�� ����Ǿ��ֳ�
	isConnected = false;
	for (int i = 0; i < adjacent_List[4].size(); i++) {
		if (adjacent_List[4][i] == 5)
			isConnected = true;
	}

	if (isConnected)
		cout << "5�� 4�� ����Ǿ�����" << endl;

	//0�� 2 ���Ῡ�� �������
	if (adjacent[0][2] && adjacent[2][0])
		cout << "0�� 2�� ����Ǿ�����" << endl;

	//5�� 4 ���Ῡ�� �������
	if (adjacent[5][4] && adjacent[4][5])
		cout << "5�� 4�� ����Ǿ�����" << endl;

	return 0;
}