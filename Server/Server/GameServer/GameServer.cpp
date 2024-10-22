#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"
#include "RefCounting.h"

using PlayerRef = shared_ptr<class Player>;
using InventoryRef = shared_ptr<class Inventory>;

class Player
{
public:
	Player() 
		:_hp(0), _atk(0)
	{
		cout << "생성자 호출" << endl;
	}
	Player(int hp, int atk)
		: _hp(hp), _atk(atk)
	{
		cout << "타입 변환 생성자 호출" << endl;
	}
	virtual ~Player() 
	{
		cout << "소멸자 호출" << endl;
	}

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

class Knight : public Player
{
public:
	int _stamina = 0;
};

int main()
{
	CoreGlobal::Create();

	for (int32 i = 0; i < 5; i++)
	{
		TM_M->Launch([]()->void
			{
				while (true)
				{
					Vector<Knight> v(10);

					Map<int32, Knight> m;
					m[1] = Knight();

					this_thread::sleep_for(500ms);
				}
			});
	}

	while (true)
	{
		Knight* k = xnew<Knight>();

		xrelease(k);
	}

	CoreGlobal::Delete();
}