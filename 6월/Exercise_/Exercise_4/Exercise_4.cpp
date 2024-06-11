#include <iostream>
using namespace std;
#include "Knight.h"

// [Bug Report #4]
// "생명력 구슬"을 도입해서 이 구슬을 먹으면 
// 랜덤으로 체력을 올려주도록 합니다.
// 이 기능이 잘 동작하는지 100% 확신하기 위해 
// HP를 100만 채우는 테스트를 100만 번 합니다.
// 그런데 어째서일까요? 분명히 체력을 채워줬는데,
// 결과를 보니 기사가 죽었네요...?
// 구슬에 독약이라도 탄걸까요?
// "생명력 구슬"은 현금으로 판매할 중요한 수입원입니다.
// 하루 빨리 원인을 파악해주세요!!

int main()
{
	Knight* k1 = new Knight();
	k1->_hp = 100;
	k1->_attack = 10;

	const int TEST_COUNT = 100 * 10000; // 100만
	const int TEST_VALUE = 100 * 10000; // 100만

	for (int i = 0; i < TEST_COUNT; i++)
	{
		k1->AddHp(TEST_VALUE);
	}

	if (k1->IsDead())
	{
		cout << "죽었습니다!" << endl;
	}
	else
	{
		cout << "엥? 살았습니다!" << endl;
	}

	delete k1;
}
