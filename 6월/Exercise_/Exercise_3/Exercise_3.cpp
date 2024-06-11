#include <iostream>
using namespace std;
#include "Knight.h"

// [Bug Report #3]
// 우여곡절 끝에 버그#1, #2가 해결된 것으로 판단됩니다.
// 이제 데미지 피격 실험을 해보기 위해
// Knight1의 스탯을 (100/10)으로,
// Knight2의 스탯을 (2000/200)으로 올렸습니다.
// Knight2가 Knight1를 한방에 처치해야 하는데...
// 왜일까요? 죽었다는 로그가 뜨지 않습니다.
// 문제 원인을 파악해서 수정해주세요!

int main()
{
	Knight* k1 = new Knight();
	k1->_hp = 100;
	k1->_attack = 10;

	Knight* k2 = new Knight();
	k2->_hp = 2000;
	k2->_attack = 200;

	int damage = k2->_attack;
	k1->AddHp(-damage);

	if (k1->IsDead())
	{
		cout << "죽었습니다!" << endl;
	}
	else
	{
		cout << "엥? 살았습니다!" << endl;
	}

	delete k1;
	delete k2;
}
