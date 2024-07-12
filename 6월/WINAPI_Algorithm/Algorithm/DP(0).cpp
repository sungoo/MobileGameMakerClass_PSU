#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//DP
// 1. �޸������̼�
// - ��������, �޸������̼�, ���ϱ�
// ==> �����κб���(����)�� �˾ƾ��Ѵ�. 
// (�����κб��� = �ݺ��Ǵ� �κ�. ���⼱ ��ȭ��)
//

//Fibonacci ����

int Mcount = 0;

//�޸������̼� ... memo
vector<int> chache = vector<int>(100, -1);

int Fibonacci(int i)
{
	//��������
	if (i == 0 || i == 1)
		return 1;

	//�޸������̼�
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