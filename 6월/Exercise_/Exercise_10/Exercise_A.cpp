#include <iostream>
using namespace std;
#include "Knight.h"
#include "Archer.h"
#include "Mage.h"
#include "Pet.h"
#include "Arrow.h"

// [Bug Report #10]
// 궁수라며면 자고로 화살을 쏴야겠죠.
// Arrow는 자신을 목표 대상물을 target으로 관리하고
// Arrow를 만들 때 설정한 데미지 만큼 target의 체력을 깎습니다.
// 테스트를 위해 화살 10개를 생성해서 기사를 피격했는데...
// C++이 늘 그렇지만 되는 일이 없고 또 크래시가 납니다.
// 뭐가 문제일까요?

//new / delete
//=> C++ 11
// 스마트 포인터 추가됨.
//

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	//스마트 포인터 아쳐 => delete가 필요 없음.
	shared_ptr<Archer> archer = make_shared<Archer>(new Pet());
	archer->_hp = 100;
	archer->_maxHp = 100;
	archer->_attack = 20;

	Knight* knight = new Knight();	
	knight->_hp = 150;
	knight->_maxHp = 150;
	knight->_attack = 10;
	
	Arrow* arrows[10] = {};
	for (int i = 0; i < 10; i++)
	{
		// 기사를 타겟으로, 궁수의 공격력을 지닌 상태
		Arrow* arrow = new Arrow(knight, archer->_attack);
		arrows[i] = arrow;
	}

	for (int i = 0; i < 10; i++)
	{
		arrows[i]->AttackTarget();

		// 기사가 죽었으면 소멸시켜준다
		if (knight != nullptr)
		{
			if (knight->IsDead())
			{
				cout << "Knight는 죽었습니다." << endl;
				break;
			}
		}	
		
	}
	for (int i = 0; i < 10; i++) {
		delete arrows[i];
		arrows[i] = nullptr;
	}
	delete knight;
}
