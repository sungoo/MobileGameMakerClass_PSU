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
	~Player() 
	{
		cout << "소멸자 호출" << endl;
	}

	/*static void* operator new(size_t t)
	{
		cout << "Player new!!" << endl;
		void* ptr = std::malloc(t);

		return ptr;
	}

	static void operator delete(void* ptr)
	{
		cout << "Player delete!!" << endl;
		std::free(ptr);
	}*/

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

//void* operator new(size_t t)
//{
//	cout << "new!!" << endl;
//	void* result = std::malloc(t);
//
//	return result;
//}
//
//void operator delete(void* ptr)
//{
//	cout << "delete!!" << endl;
//	std::free(ptr);
//}

int main()
{
	
	CoreGlobal::Create();

	Player* p = xnew<Player>(100, 10);

	xdelete(p);

	CoreGlobal::Delete();
}