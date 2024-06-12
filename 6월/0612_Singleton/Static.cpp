#include <iostream>

using namespace std;

//디자인 패턴
//		프로그래밍 하면서 공통된 문제들을 해결하는 패턴을 정형화 해놓은 것
// 
// 1. 싱글톤(Singleton)
// - 객체를 단 하나만.
// - ex) 게임 로직을 담당하는 애들, 시스템적인 면을 담당하는 애들
// - SoundManager
//	... 사운드 출력할 때 마다 동적할당을 한다..?	=> 동적할당은 무거워서 부하가 많이 걸림
//  ... 객체 하나마다 사운드를 다 가진다..?			=> 사운드 파일 자체가 무거워서 로딩이 오래 걸리게 됨
// => SoundManager에 전사 10명의 목소리, 도적 10명의 목소리 저장, 관리

//Static 변수 / 함수
//

//메모리 영역
// - Code
// - Data
//	=> 전역변수(Global), 정적변수(Static)
//  => 프로그램이 시작될 때 ~ 프로그램이 종료될 때
// - Stack
//  => [반환주소값][지역변수][매개변수]
//  => 함수 호출 시, 지역 시작 ~ 함수 종료 시, 지역 끝
// - Heap
//  => 내가 원하는 데이터 크기만큼
//  => 프로그래머가 원하는 대로 시작과 종료
//

class Marine {
public:
	void Print() {
		cout << _hp << endl;
		cout << atk << endl;//멤버함수에서 정적멤버변수 읽기 가능
	}
	void Set(int hp, int atk) {
		_hp = hp;
		this->atk = atk; //맴버함수에서 정적맴버변수 쓰기 가능
	}

	//정적맴버함수
	//맴버함수 호출 조건 : 객체가 무조건 있어야한다.
	//정적맴버함수...전역함수 처럼 쓸 수 있다. => 객체가 없어도 쓸 수 있다.
	static void Print_S() {
		//cout << this->_hp << endl;  맴버변수에 접근할 수 없음 == this를 특정할 수 없음.
		cout << atk << endl;		//정적맴버변수에 접근할 수 있음
	}

	int _hp;
	static int atk;

};
//외부에서 초기화 가능
int Marine::atk = 1;

Marine* marines[100];

int main() {
	
	for (int i = 0; i < 100; i++) {
		marines[i] = new Marine();
	}

	Marine::atk++;

	marines[0]->Set(100, 50);
	Marine::Print_S();

	cout << marines[5]->atk << endl;

	return 0;
}