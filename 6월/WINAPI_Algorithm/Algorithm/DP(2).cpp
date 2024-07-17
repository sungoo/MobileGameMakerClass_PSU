#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//LIS (Longest Increasing Subsequence)
//���� ���� �κ� ����

vector<int> v = { 5, 13, 2, 1,10,15 };
//�׳� �κ� ���� : { 2, 1, 10 }, { 5, 2, 15 }
//���� �κ� ���� : { 5, 13 }, { 13, 15 } 
//   => �κм��� �߿����� ���� �����ϴ� ����
//���� ���� �κ� ���� : { 1, 10, 15 } , { 5, 10, 15 } 
//   => ���� �κ� ���� �߿��� ���� ���� ���� ���� ����

vector<int> a = { 3, 5, 7, 9, 1, 4, 8 };
vector<int> cache;

int FindLIS(int here)
{
	if (here == a.size() - 1)
		return 1;

	//�޸������̼�
	int& ref = cache[here];
	if (ref != -1)
		return ref;

	ref = 1;
	for (int there = here+1; there < a.size(); there++) {
		//���� ���Ұ� �̹� ���Һ��� ���� => ���� ����
		if (a[here] <= a[there])
		{
			ref = max(ref, FindLIS(there)+1);
		}
		
	}
	return ref;
}

int main() {

	cache = vector<int>(v.size(), -1);
	int lis = 1;

	for (int i = 0; i < a.size(); i++) {
		lis = max(lis, FindLIS(i));
	}

	cout << lis << endl;

	return 0;
}