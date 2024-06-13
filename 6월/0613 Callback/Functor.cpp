#include <iostream>

using namespace std;

//Functor = Func + Actor
//함수객체
//객체이고, 함수처럼 쓸 수 있는 객체
// ()함수 연산자를 오버로드해서 쓸 수 있음.
// 콜백개념으로 쓸 수 있다.
// [함수 포인터와의 차이점]
// = 속성(맴버변수)을 가질 수 있다.
//
struct Functor {//struct 또한, 기본 접근지정자가 public이란 차이가 있을 뿐, 객체다.

	int _aInt;
	int _bInt;

	Functor():_aInt(3), _bInt(5)
	{
		cout << "Functor 생성" << endl;
	}

	//연산자 오버로딩
	void operator()() {//() : 함수 연산자
		cout << "HelloWorld" << endl;
		cout << _aInt + _bInt << endl;
	}
	//매개변수 받는 형태
	void operator()(int number) {
		cout << number << endl;
	}
};

class Player {

	Functor* _functor;

public:
	void Excute() {
		if (_functor != nullptr)
			(*_functor)();
	}

	void SetFunctor(Functor* functor) {
		_functor = functor;
	}
};



int main() {
	Functor functor;

	functor();
	functor(1);

	functor._aInt = 9;
	functor._bInt = 10;
	functor();
}