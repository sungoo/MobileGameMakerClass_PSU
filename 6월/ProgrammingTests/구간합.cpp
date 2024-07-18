#include <iostream>
#include <vector>

using namespace std;

int N = 0;
int M = 0;
vector<int> v;
vector<vector<int>> sub;

void Input()
{
	cin >> N;
	cin >> M;

	v.reserve(N);
	sub.reserve(M);

	for (int i = 0; i < N; i++)
	{
		int temp = 0;
		cin >> temp;
		v.push_back(temp);
	}

	for (int j = 0; j < M; j++)
	{
		vector<int> temp;
		int a = 0;
		int b = 0;
		cin >> a;
		cin >> b;

		temp.push_back(a);
		temp.push_back(b);

		sub.push_back(temp);
	}
}

vector<int> sumArr;
void CreateSumArr()
{
	sumArr.reserve(N);

	sumArr.push_back(v[0]);
	for (int i = 0; i < N; i++)
	{
		int temp = sumArr[i] + v[i + 1];
		sumArr.push_back(temp);
	}
}

int main()
{
	Input();
	CreateSumArr();

	for (int i = 0; i < M; i++)
	{
		int a = sub[i][0];
		int b = sub[i][1];
		if (a == 1)
		{
			cout << sumArr[b - 1] << "\n";
		}
		cout << sumArr[b - 1] - sumArr[a - 2] << "\n";
	}
}