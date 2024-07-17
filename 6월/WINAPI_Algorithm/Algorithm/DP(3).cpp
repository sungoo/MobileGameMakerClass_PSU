#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

//Enchant
// N만큼 강화
// +1 +2 +3

// 1
// +1
// ...E(1) = 1
// 
// 2
// +1 +1
// +2
// ...E(2) = E(1) + 1
//
// 3
// +1 +1 +1
// +1 +2
// +2 +1
// +3
// ... result = 4
// ...E(3) = E(2) + E(1) + 1
// 
// 4
// +1 +1 +1 +1
// +1 +1 +2
// +1 +2 +1
// +1 +3   ///////여기까지 N = 3일 때 + 1 한 부분
// +2 +1 +1
// +2 +2
// +3 +1
// ... result = 7
// ... E(4) = E(3) + E(2) + E(1)

vector<int> cache = vector<int>(100001, -1);

int Enchant(int num)
{
	//기저사항
	if (num == 0)
		return 1;
	if (num < 0)
		return 0;

	//메모이제이션
	int& ref = cache[num];
	if (ref != -1)
		return ref;

	//구하기
	return ref = Enchant(num - 1) + Enchant(num - 2) + Enchant(num - 3);
}

int main() {
	int result = Enchant(4);

	cout << result << endl;

	return 0;
}