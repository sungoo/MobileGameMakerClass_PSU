#include <iostream>

using namespace std;

//함수도 어딘가에는 저장되어있지 않을까.
// 
//함수 이름이 포인터와 동일하게 동작한다.
// = 배열과 비슷

//콜백함수
//함수가 인자로 넘겨진다.

void HelloWorld() {
    std::cout << "Hello World!\n";
}

void PrintHello() {
    cout << "안녕하세요" << endl;
}

void PrintNum(int num) {
    cout << num << endl;
}

//함수 포인터
//함수 선언 방법 : (반환자료형) 함수이름 (매개변수) => 함수 시그니처

//(반환 자료형) (*포인터 이름)(매개변수)
void(*func)(void);
void(*fund)(int);

class Pet {

public:
    void Sound() {
        cout << "야옹" << endl;
    }

    static void DogSound() {
        cout << "멍멍" << endl;
    }
};
//멤버함수 포인터
void(Pet::* funP)(void);

class Player {

    void(*_func)(void) = nullptr;
    void(Pet::* _petFunc)(void) = nullptr;
    Pet* _pet = nullptr;

public:
    void Excute() {
        if (_func != nullptr)
            _func();
    }
    //맴버함수는 객체가 있어야만 호출할 수 있다.
    void PetExcute() {
        if (_petFunc != nullptr && _pet != nullptr)
            (_pet->*_petFunc)();
    }

    void SetFunc(void(*func)(void)) {
        _func = func;
    }
    void SetPetFunc(Pet* pet, void(Pet::* func)(void)) {
        _petFunc = func;
        _pet = pet;
    }
};

int main()
{
    func = &HelloWorld;
    fund = &PrintNum;
    func();

    Player* p = new Player();
    p->SetFunc(PrintHello);
    p->Excute();

    Pet* pet = new Pet();
    p->SetPetFunc(pet, &Pet::Sound);
    p->PetExcute();
    //세팅(set)과 호출(excute)이 분리된다. => 호출시점을 마음대로 설정 가능하다.

    //정적 맴버함수는 일반 함수 콜백과 똑같이 작동한다. 대신, 어떤 객체의 함수인지는 알려야 함.
    p->SetFunc(&Pet::DogSound);
    p->Excute();

    delete pet;
    delete p;
}
