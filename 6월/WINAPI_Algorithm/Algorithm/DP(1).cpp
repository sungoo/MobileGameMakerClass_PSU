#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//������ ��ȭ��
// nCr = n-1Cr + n-1Cr-1

//n <= 100
//r <= 100
vector<vector<int>> cache = vector<vector<int>>(101,vector<int>(101, -1));

int Combination(int n, int r)
{
	//��������
	if (r == 0 || n == r)//������ ���ų� n�� �� n���� �̱� = 1���� ����� ��
		return 1;
	if (r == 1)//n�� �� 1�� �̱� = n���� ����� ��
		return n;

	//�޸������̼�
	int& ref = cache[n][r];
	if (ref != -1) {
		return ref;
	}

	//���ϱ�
	ref = Combination(n - 1, r) + Combination(n - 1, r - 1);

	return ref;
}

int main()
{
	//cout << Combination(10, 4) << endl;

	vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };

	//7P3
	int count = 1;
	while (true)
	{
		if (std::next_permutation(v.begin(), v.begin()+4))
		{
			count++;
			cout << v[0] << v[1] << v[2] << v[3] << endl;
		}
		else
			break;
	}

	cout << count << endl;

	return 0;
}