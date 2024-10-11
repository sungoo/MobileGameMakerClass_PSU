#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"
#include "RefCounting.h"

using PlayerRef = TSharedPtr<class Player>;

class Player : public RefCountable
{
public:
	void Attack()
	{
		if (_target != nullptr)
		{
			_target->_hp -= _atk;
		}
	}

	bool IsDead()
	{
		return _hp <= 0;
	}

public:
	PlayerRef _target;
	int _hp;
	int _atk;
};


int main()
{
	CoreGlobal::Create();

	PlayerRef p1 = new Player();
	p1->ReleaseRef();
	p1->_hp = 10000;
	p1->_atk = 15;

	PlayerRef p2 = new Player();
	p2->ReleaseRef();
	p2->_hp = 20000;
	p2->_atk = 15;

	//Shared Ptr 의 순환참조 문제
	p2->_target = p1;
	//p1->_target = p2;

	while (true)
	{
		if (p1 != nullptr)
		{
			p2->Attack();
			if (p1->IsDead())
			{
				p1 = nullptr;
				break;
			}
		}
	}

	CoreGlobal::Delete();
}