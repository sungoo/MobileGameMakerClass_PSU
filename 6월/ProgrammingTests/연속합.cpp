#include <iostream>
#include <vector>

using namespace std;

vector<int> nums;
int sizeN;
vector<int> cache;

int squinceAdd(int here)
{
	//기저
	if (here == sizeN - 1)
		return nums[here];


	cache = vector<int>(sizeN, -1001);
	int& ref = cache[here];
	if (ref != -1)
	{
		return ref;
	}
	//구하기
	int result = nums[here];
	result = max(result, result + squinceAdd(here + 1));
	ref = result;

	return ref;

}

void Input()
{
	cin >> sizeN;
	
	for (int i = 0; i < sizeN; i++)
	{
		int temp = 0;
		cin >> temp;
		nums.push_back(temp);
	}
}

int main()
{
	sizeN = -1;
	int result = -1001;

	Input();

	for (int i = 0; i < sizeN; i++)
	{
		result = max(result, squinceAdd(i));
	}

	cout << result << endl;

}