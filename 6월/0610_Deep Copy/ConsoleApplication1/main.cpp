#include <iostream>

using namespace std;

class Pet {

};

class Player {
public :
	//생성자 : 기본생성자 , 타입변환 생성자

	//기본생성자
	Player() : 
		//빠른초기화 영역. 여기선 상수 초기화 가능
		hp(0), 
		maxhp(150), 
		hpRef(hp),
		target(nullptr),
		pet(nullptr)
	{
		hp = maxhp;
		pet = new Pet();
		cout << "기본생성자 호출" << endl;
	}

	//타입변환 생성자
	Player(int hp) :
		hp(hp),
		maxhp(150),
		hpRef(hp),
		target(nullptr),
		pet(nullptr)
	{
		hp = maxhp;
		pet = new Pet();
		cout << "타입변환 생성자 호출" << endl;
	}

	//복사생성자
	//암묵적으로 만들어주는 생성자 // 명시적으로 만들면 안 만들어줌 // 암묵적으로 만든거 : 얕은복사 ShallowCopy
	//암묵적으로 만들었을 때, 모든 멤버변수를 복사한다.
	Player(const Player& other)
		: maxhp(other.maxhp),
		hp(other.hp),
		hpRef(other.hpRef),
		target(other.target),
		pet(nullptr)
	{
		hp = maxhp;
		pet = new Pet(*other.pet);//DeepCopy 깊은 복사
		cout << "복사생성자 호출" << endl;
	}

	~Player(){
		delete pet;
	}

	void SetTarget(Player* other) {
		target = other;
	}
	void Attack() {
		cout << "공격!" << endl;
		target->hp -= 10;
	}

private:
	//기본자료형
	int hp;
	
	const int maxhp;
	int& hpRef;//별명
	Player* target;
	Pet* pet; //4 bite
};

int main() {
	Player a = Player();//기본생성자 호출
	Player b = Player(5);//타입변환 생성자 호출
	Player c = 2;//타입변환생성자 호출
	Player d = Player(c);//복사생성자 호출

	cout << endl;

	Player* mPlayer = new Player();//기본생성자
	Player* bPlayer = new Player(5);//타입변환생성자
	Player* cPlayer = new Player(2);//타입변환생성자
	Player* dPlayer = new Player(*cPlayer);//복사생성자  //*cPlayer : 간접연산자. 포인터 파고들기. 결국은 cPlayer가 가르키는 new Player(2)

	Player* a_p = new Player();
	Player* b_p = new Player(*a_p);

	delete a_p;
	delete b_p;

	delete dPlayer;
	delete cPlayer;
	delete bPlayer;
	delete mPlayer;
}