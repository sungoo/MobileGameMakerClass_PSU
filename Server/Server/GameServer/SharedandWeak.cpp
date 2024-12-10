#include "pch.h"
#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"
#include "RefCounting.h"

using PlayerRef = shared_ptr<class ChatPlayer>;
using InventoryRef = shared_ptr<class Inventory>;

class ChatPlayer
{
public:
	ChatPlayer() {}
	~ChatPlayer() {}

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
	weak_ptr<Inventory> _inven;

	int _hp;
	int _atk;
};

class Inventory
{
public:
	Inventory(PlayerRef p) :_owner(p) { } //스마트 포인터의 참조 카운트를 올리지 않으면서 참조

	void OpenInven()
	{
		if (_owner.expired() == false)
		{
			auto ptr = _owner.lock();
			if (ptr != nullptr)
				cout << ptr->_hp << ptr->_atk << endl;
		}
	}
public:
	//Player& _owner;
	weak_ptr<ChatPlayer> _owner;
};


int main()
{
	//Shared_ptr
	// - 참조 카운터
	// - 순환 참조 문제

	//Weak_ptr
	// - Weak Counting을 한다.
	// - 순환 참조 문제를 해결하기 위해 쓰이는 ptr
	// - 생성주기에 관여하지 않는다.
	//


	CoreGlobal::Create();

	PlayerRef p = make_shared<ChatPlayer>();
	InventoryRef inven = make_shared<Inventory>(p);
	p->_inven = inven;
	// => 순환참조

	inven->OpenInven();

	//p->_inven = nullptr;
	//inven->_owner = nullptr;
	//순환참조 고리 끊기

	CoreGlobal::Delete();
}