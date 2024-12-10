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
	ChatPlayer()
		:_hp(0), _atk(0)
	{
		cout << "생성자 호출" << endl;
	}
	ChatPlayer(int hp, int atk)
		: _hp(hp), _atk(atk)
	{
		cout << "타입 변환 생성자 호출" << endl;
	}
	~ChatPlayer()
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

class Knight : public ChatPlayer
{
public:
	int _stamina = 0;
};

//선수지식
// - 허상포인터로 인한 메모리 오염
// - 가상메모리와 물리적 메모리
// - 사실 new와 delete는 바로바로 일을 해준 것이 아니었다. 
//		=> delete가 실제로 바로 삭제하는게 아니었다.
//		=> 허상포인터의 데이터를 수정할 수 있었다.
//

// Stomp Alloocator의 의미
// 1. DEBUG 환경에서 메모리 오염 방지
// 2. DEBUG 환경에서 다운캐스팅 후 메모리 오버플로 방지
//

int main()
{
	CoreGlobal::Create();

#pragma region 가상메모리와 운영체제
	ChatPlayer* p = new ChatPlayer();

	//허상 포인터(Dangling Pointer)
	p->_atk = 10;
	p->_hp = 10;

	delete p;
	//p = nullptr;//허상 포인터 막기

	p->_hp = 50; //메모리 오염

	//가상 메모리
	p = nullptr;

	p = new ChatPlayer();

	//------------다른 프로그램-------------
	//int64* temp = (int64*)(p);
	//*temp = 500;
	//=> 바뀌지 않는다.
	// 원래 프로그램과 다른 프로그램의 가상메모리가 다르기 때문
	//--------------------------------------

	//운영체제 페이징
	//운영체제가 메모리를 할당하고 관리할 때는 페이지 단위로 관리를 한다.
	//각 프로세스한테 가상메모리를 주고 유저레벨에서 서로 간섭할 수 없게 만든다.
	// => 물리적 메모리는 운영체제가 담당한다.
#pragma endregion

	SYSTEM_INFO s_info;
	::GetSystemInfo(&s_info);

	s_info.dwPageSize; //페이지 한 개당 사이즈 4KB
	s_info.dwAllocationGranularity;//메모리를 할당할 때 이 숫자의 배수로 할당이 된다.

	//Window API
	int* temp = (int*) ::VirtualAlloc(nullptr, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	*temp = 100;

	::VirtualFree(temp, 0, MEM_RELEASE);

	*temp = 200; //런차임 에러 바로 발생.
	// => new / delete : VirtualAlloc, VirtualFree를 바로 해주지 않는다.

	//4096 bytes
	//[[p2]100									]
	//[										[p2]]100 (x)
	//test
	Knight* k = reinterpret_cast<Knight*>(new ChatPlayer());
	// k->_stamina = 100; => 메모리 오버플로우
	//std::new / delete Allocator 상속 구조에서 메모리 오버플로우를 허용하지 않음

	delete k;

	Knight* p2 = reinterpret_cast<Knight*>(xnew<ChatPlayer>());
	p2->_hp = 100;//메모리 오버플로우 막음

	xdelete(p2);

	//p2->_hp = 200;

	CoreGlobal::Delete();
}