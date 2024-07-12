#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//DP
// 1. 메모이제이션
// - 기저사항, 메모이제이션, 구하기
// ==> 최적부분구조(문제)를 알아야한다. 
// (최적부분구조 = 반복되는 부분. 여기선 점화식)
//

//Fibonacci 수열

int Mcount = 0;

//메모이제이션 ... memo
vector<int> chache = vector<int>(100, -1);

int Fibonacci(int i)
{
	//기저사항
	if (i == 0 || i == 1)
		return 1;

	//메모이제이션
	int& ref = chache[i];
	if (ref != -1)
		return ref;

	if (i == 2)
		Mcount++;

	ref = Fibonacci(i - 1) + Fibonacci(i - 2);

	return ref;
}

int main()
{
	__int64 start = GetTickCount64();


	cout << Fibonacci(40) << endl;

	__int64 end = GetTickCount64();

	cout << end - start << "ms, count : " << Mcount << endl;
	return 0;
}