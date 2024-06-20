#include <iostream>
#include <memory>

#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

//shared_ptr

//weak_ptr

//unique_ptr

class Player {
public:
	Player() {
		cout << "기본생성자 호출" << endl;
	}
	Player(int hp):_hp(hp) {
		cout << "타입 변환 생성자 호출" << endl;
	}
	~Player() {
		cout << "소멸자 호출" << endl;
	}

	void Attack() {
		if (target.expired() == false) {
			target.lock()->_hp -= 10;
			cout << "공격!!" << endl;
		}
	}
	void SetTarget(shared_ptr<Player> target) {
		this->target = target;
	}
private:
	weak_ptr<Player> target;

	int _hp = 0;
};
#pragma region MySharedPtr
struct RefCountBlock {
	int refCount = 1;
};

template<typename T>
class SharedPtr {
	RefCountBlock* _block;
	T* _ptr;
public:
	SharedPtr(T* ptr) : _block(nullptr), _ptr(ptr) 
	{
		_block = new RefCountBlock();
		cout << "RefCount : " << _block->refCount << endl;
	}
	SharedPtr(const SharedPtr<T>& other) :
	_ptr(other._ptr),
	_block(other._block)
	{
		if (_ptr != nullptr) {
			_block->refCount++;
			cout << "RefCount : " << _block->refCount << endl;
		}
	}

	~SharedPtr() {
		if (_ptr != nullptr) {
			_block->refCount--;
			cout << "RefCount : " << _block->refCount << endl;

			if (_block->refCount <= 0) {
				delete _block;
				delete _ptr;
				_ptr = nullptr;
			}
		}
	}

	SharedPtr<T>& operator=(const SharedPtr<T>& other) {
		_ptr = other._ptr;
		_block = other._block;

		if (_ptr != nullptr) {
			_block->refCount++;
			cout << "RefCount : " << _block->refCount << endl;
		}

		return (*this);
	}

	T* operator->() {
		if (_ptr != nullptr)
			return _ptr;
		return nullptr;
	}
};

//void PrintPlayer(SharedPtr<Player> pl) {
//	cout << pl->_hp << endl;
//}
#pragma endregion

int main() {

	shared_ptr<Player> p1 = make_shared<Player>(5);
	shared_ptr<Player> p2 = make_shared<Player>(10);

	//shared_ptr의 순환참조 문제 : 
	// 타겟으로 다른 개체를 물고 들어가면서 복사생성자가 호출됨. 끝나고서 소멸되지 않으니 RefCount가 줄어들지 않아, 소멸되질 않음.
	// weak_ptr은 이걸 해결하기 위해 존재 : RefCount를 하나 더 들고있음.
	p1->SetTarget(p2);
	p2->SetTarget(p1);

	p1->Attack();
	p2->Attack();

	p1->SetTarget(nullptr);
	p2->SetTarget(nullptr);

	//unique_ptr
	unique_ptr<Player> p3 = make_unique<Player>();

	return 0;
}