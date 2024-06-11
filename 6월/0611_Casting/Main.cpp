#include <iostream>

using namespace std;

//캐스팅

//C스타일 캐스팅
//기본자료형 캐스팅 (안전!)

//C++ 스타일 캐스팅(4총사)
//1. Static Cast
//=> 상식적인 변환만 허용
//=> 컴파일 시간에 캐스팅

//2. Dynamic Cast
// => 상속 구조에서 다형성(vftable)이 있어야 사용 가능
// => 캐스팅이 실패하면 nullptr을 반환한다.
// => 런타임 중 캐스팅

//3. Const Cast
// => 상수객체를 비상수객체로 캐스팅

//4. Reinterpret Cast
// => 모든 형변환을 허용
//

class Player {
public:
	virtual void PrintPlayer() { cout << "Player입니다." << endl; }
};
class Knight :public Player {
public:
	virtual void PrintPlayer() { cout << "Knight입니다." << endl; }
};
class Mage :public Player {
public:
	virtual void PrintPlayer() { cout << "Mage입니다." << endl; }
	int mana;
};

void ManaUp(Player* player) {
	Mage* mage = dynamic_cast<Mage*>(player);

	if (mage == nullptr) {
		cout << "Mage가 아닙니다." << endl;
		return;
	}

	mage->PrintPlayer();
	cout << "최대 마나가 증가했습니다!" << endl;
}

//pkt : 17kb/s (초당 패킷 전송량), fps 140
enum PacketID {
	NONE = 0,
	LOG_IN,
	LOG_SUCCESS,
	CREATE_ACCOUNT,
	PLAYER_RUN,
};

struct Protocol_test_S {//Server로 보내기
	PacketID pid = PacketID::LOG_IN;
	int id;
	int password;
};
struct Protocol_test_C {//Client로 보내기
	PacketID pid = PacketID::LOG_SUCCESS;
	bool succeed;
};

int main() {
	int aint = 5;
	float afloat = static_cast<float>(aint); // 16진수 => 부동소수점
	bool abool = (bool)aint;
	//int* aptr = (int*)aint; //...aptr == 5

	Player* player1 = new Knight();
	//int* aptr = static_cast<int*>(player);
	//int* aptr = reinterpret_cast<int*>(player);
	Player* player2 = new Mage();

	ManaUp(player1);
	ManaUp(player2);

	//리터럴 상수
	//char* str1 = "Hello"; //rodata

	//Data 영역
	//- bss		: 초기화되지 않은 전역변수
	//- data	: 초기화된 전역변수
	//- rodata	: 상수

	char* str1 = const_cast<char*>("Hello"); //통과는 되는데, 수정은 불가.
	str1[1] = 'z';

	//클라이언트 로그인 시도
	Protocol_test_S pkt;
	pkt.pid = PacketID::LOG_IN;
	pkt.id = 12345;
	pkt.password = 12345;

	//서버에서 로그인 체크 후 성공여부 전달
	Protocol_test_S* s_pkt = reinterpret_cast<Protocol_test_S*>(&pkt);

	//클라이언트에서 로그인 성공여부
}