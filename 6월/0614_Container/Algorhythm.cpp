#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool Func(const int& val) {
	if (val > 15)
		return true;
	return false;
}

void X3(int& val) {
	val *= 3;
}

int main() {

	vector<int> mVec;

	mVec.push_back(3);
	mVec.push_back(5);
	mVec.push_back(7);
	mVec.push_back(9);
	mVec.push_back(1);

	mVec.push_back(21);
	mVec.push_back(4);
	mVec.push_back(6);
	mVec.push_back(8);
	mVec.push_back(1);

	//1_ 1이 있는지 찾기. 그리고 index 혹은 iterator자리 반환
	int index = 0;
	for (index; index < mVec.size(); index++) {
		if (mVec[index] == 1) break;
	}
	if (index == mVec.size())
		cout << "인덱스로 1 발견 못함." << endl;
	else
		cout << "인덱스로 1 발견. 위치 : " << index+1 << endl;
	
	vector<int>::iterator mit = mVec.begin();
	for (mit; mit != mVec.end(); mit++) {
		if (*mit == 1) break;
	}
	if (mit == mVec.end())
		cout << "이터레이터로 1 발견 못함." << endl;
	else
		cout << "이터레이터로 1 발견. 위치 : " << &*mit << endl;

	mit = std::find(mVec.begin(), mVec.end(), 1);
	if (mit != mVec.end())
		cout << *mit << endl;
	//2_ 15보다 큰 수가 있는지 찾고 index 혹은 iterator 자리 반환
	struct Finder_1 {
		bool operator()(const int& val) {
			if (val > compareNum)
				return true;
			return false;
		}
		int compareNum = 0;
	};
	Finder_1 finder_1;

	finder_1.compareNum = 15;
	mit = std::find_if(mVec.begin(), mVec.end(), finder_1);//find_if엔 전역함수와 정적함수만 넣을 수 있음
	cout << *mit << endl;

	//3_ 모든 수가 50보다 작은지 bool로 알리기
	struct Finder_2
	{
		bool operator()(const int& val) {
			if (val < compareNum)
				return true;
			return false;
		}
		int compareNum = 0;
	};
	Finder_2 finder_2;
	finder_2.compareNum = 50;

	bool istrue = std::all_of(mVec.begin(), mVec.end(), finder_2);
	if (istrue)
		cout << "모든 수가 50보다 작음" << endl;
	else
		cout << "50 이상의 수가 있음" << endl;

	//4_ 하나라도 30보다 큰 수가 있는지 bool로 알리기
	finder_1.compareNum = 30;
	istrue = std::any_of(mVec.begin(), mVec.end(), finder_1);
	if (istrue)
		cout << "30보다 큰 수가 있음" << endl;
	else
		cout << "30보다 큰 수가 없음" << endl;

	//5_ 원소가 3인 원소들의 개수를 알아내기
	
	int cnt = std::count(mVec.begin(), mVec.end(), 3);
	cout << "3인 원소의 개수 : " << cnt << endl;

	//6_ 원소가 5 이상인 것의 개수를 알아내기
	finder_1.compareNum = 4;
	cnt = std::count_if(mVec.begin(), mVec.end(), finder_1);
	cout << "5 이상 원소의 개수 : " << cnt << endl;

	//7_ 모든 원소에 3 곱하기
	cout << "모든 원소 3 곱하기" << endl;
	for_each(mVec.begin(), mVec.end(), X3);
	
	for (mit = mVec.begin(); mit != mVec.end(); mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	//8_ 중복 원소 제거하기
	cout << "중복 원소 제거" << endl;
	
	auto it = std::unique(mVec.begin(), mVec.end());

	mVec.resize(std::distance(mVec.begin(), it));

	for (mit = mVec.begin(); mit != it; mit++) {
		cout << *mit << ' ';
	}
	cout << endl;
	//9_ 원소가 12인 것 지우기
	cout << "remove 12" << endl;
	it = std::remove(mVec.begin(), mVec.end(), 12);
	for (mit = mVec.begin(); mit != it; mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	//10_ 원소가 10보다 작은거 지우기
	finder_2.compareNum = 10;
	cout << "remove x < 10" << endl;
	it = std::remove_if(mVec.begin(), mVec.end(), finder_2);
	for (mit = mVec.begin(); mit != it; mit++) {
		cout << *mit << ' ';
	}
	cout << endl;

	return 0;
}