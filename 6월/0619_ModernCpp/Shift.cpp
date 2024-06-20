#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

//이동(이사)
//
//

class Pet {

};

class Player {
public:
	Player() {
		cout << "기본 생성자 호출" << endl;
		pet = new Pet();
	}
	Player(int hp) {
		cout << "타입 변환 생성자 호출" << endl;
		pet = new Pet();
	}
	Player(const Player& other) {
		cout << "복사 생성자 호출" << endl;
		
		pet = new Pet(*other.pet);
	}

	//&& : 우측값 참조
	// 1. 원본을 전달
	// 2. 이사를 담당
	//
	Player(Player&& other) noexcept {
		cout << "이동생성자 호출" << endl;
		if (pet != nullptr)
			delete pet;

		pet = other.pet;
		other.pet = nullptr;
	}

	~Player() {
		cout << "소멸자 호출" << endl;
		if (pet != nullptr) delete pet;
	}

	Pet* pet;
};

//우측값 레퍼런스??
// Lvalue : 좌측값
// => 수정될 수 있는 값 = 어딘가에 저장되어있다.
// == 대표) 참조형
// 
// Rvalue : 우측값
// => 수정될 수 없는 값 = 상수
// == 대표) const
//

//1. Call by Value
// => 원본이 바뀌지 않는다.
// ==> 함수 내부에서 무슨짓을 해도 원본은 멀쩡
// 매개변수의 크기는 자료형에 따라 다름
//void SetPlayer(Player p) {
//
//}

//2. Call by Address
// => 원본이 바뀐다
// 매개변수의 크기는 포인터의 크기에 따름
// 단점 : 쓰기 어렵다. 잘못 쓰면 메모리 오염이 생길 수 있다.
void SetPlayer(Player* const p) {
	//p + 1; 포인터 연산이 가능
}

//3. Call by Reference
// => 원본이 바뀐다
// 매개변수의 크기는 포인터의 크기에 따름
// 장점 : 쓰기 편하다 = 메모리 오염 가능성이 낮다.
// 단점 : 쓰기 편하지만 값전달과 동일한 방식, 범용성이 낮다.
void SetPlayer(Player& p) {
	//p + 1; 포인터 연산 불가능
}

//4. 우측값 참조 전달
// => 원본에 접근 가능
// 매개변수의 크기는 포인터의 크기에 따른다..?
// - 이사(원본을 훼손할 수 있다.)
// 우측값 취급인데 수정이 가능하다(??)
// 
void SetPlayer(Player&& p, Player&& l) {
	delete p.pet;
	p.pet = l.pet;
}

int main() {
	Player* playerB = new Player();
	Player* playerA = new Player(std::move(*playerB));
	cout << "====================================" << endl;
	unique_ptr<Player> pPtr = make_unique<Player>();
	unique_ptr<Player> pPtr2 = std::move(pPtr);//pPtr은 아예 지워지고, 나중에 소멸자 호출도 pPtr2가 가진 pPtr 내용의 소멸자가 호출됨.(결국 playerA, playerB, pPtr2 객체만이 존재하는 것임)
	cout << "====================================" << endl;
	delete playerA;
	delete playerB;

}