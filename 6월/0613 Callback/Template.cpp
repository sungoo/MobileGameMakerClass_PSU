#include <iostream>

using namespace std;

//Template
// Class
// => 객체(건물)를 찍어내는 설계도
// => Template... 이 설계도를 찍어내는 틀
//

//함수 탬플릿 : 함수 찍어내기
//탬플릿 기본인자
template<class T = int>
T Add(T a, T b) {
	T c = a + b;

	return c;
}
//탬플릿의 특수화
template<>
double Add(double a, double b) {
	double c = a + b;
	cout << "Double" << endl;

	return c;
}

//클래스 탬플릿 기본인자
template <typename T>
class Player {
public:
	T _hp;
	int _mp;

	T GetHP() {
		return _hp;
	}
	void SetHP(const T& hp) {
		_hp = hp;
	}
};

//클래스 탬플릿 특수화
template<>
class Player<double> {
public:
	double _hp;
};

int main() {
	double c = Add(1.2, 2.5);
	cout << c << endl;

	Player<int> player;
	Player<double> player2;

	return 0;
}