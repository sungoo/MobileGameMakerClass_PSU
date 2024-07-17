#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//LIS (Longest Increasing Subsequence)
//최장 증가 부분 수열

vector<int> v = { 5, 13, 2, 1,10,15 };
//그냥 부분 수열 : { 2, 1, 10 }, { 5, 2, 15 }
//증가 부분 수열 : { 5, 13 }, { 13, 15 } 
//   => 부분수열 중에서도 점점 증가하는 수열
//최장 증가 부분 수열 : { 1, 10, 15 } , { 5, 10, 15 } 
//   => 증가 부분 수열 중에서 원소 수가 가장 많은 수열

vector<int> a = { 3, 5, 7, 9, 1, 4, 8 };
vector<int> cache;

int FindLIS(int here)
{
	if (here == a.size() - 1)
		return 1;

	//메모이제이션
	int& ref = cache[here];
	if (ref != -1)
		return ref;

	ref = 1;
	for (int there = here+1; there < a.size(); there++) {
		//다음 원소가 이번 원소보다 작음 => 넣지 않음
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