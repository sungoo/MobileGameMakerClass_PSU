#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

//모던 C++
// 1. auto
// => 타입 추론
// -> 반드시 초기화가 필요함
// 
// 2. 중괄호 초기화
// int a = {5};
// 
// 3. 범위기반 for문
// 
// 4. final, friend
// 
// 5. using
// => typedef와 비슷함
// => typedef와 다른 장점 : 템플릿과 호환이 된다.
// 
// 6. enum class
// enum과 다르게 int형 묵시적 형변환은 안됨. 대신 static_cast 가능.
// 
// 7. lambda
// 8. 이동 (Shift 개념)
// 9. 스마트포인터
//

class Player {
public:
    virtual void PrintP(){}

    int _hp = 0;
};

class Knight : public Player {
public:
    friend class KnightHelper;
    virtual void PrintP() final override{}
private:
    int _stamina = 0;
};

class HolyKnight : public Knight {
public:
    //virtual void PrintP() override{}
};

class KnightHelper {
public:
    void PrintK(Knight* k) { k->_stamina; }
};

void Hello() {
    cout << "HelloWorld" << endl;
}

typedef void(*FuncPtr)(void);
typedef unsigned int UNIT;

using UNIT2 = unsigned float;
using FuncPtr2 = void(*)(void);

enum class PlayerType {
    NONE,
    KNIGHT,
    ARCHER,
    MAGE,
};

enum class WarriorType {
    NONE,
    HOLLYKNIGHT,
    WARRIOR,
    KNIGHT,
};

int main()
{
    auto aint = { 5 };
    auto aDouble = { 1.43 };

    vector<int> tempv = { 1,1,2,5,7,8,99,23,223 };
    auto vit = tempv.begin();

    unordered_map<int, int> temp_M;
    temp_M[0] = 1;
    temp_M[1] = 5;
    temp_M[2] = 9;
    temp_M[3] = 2;
    temp_M[4] = 2;

    auto mit = temp_M.begin();

    ///////////////////////////

    for (int& data : tempv) {
        data = 0;
        cout << data << endl;
    }

    for (auto& p : temp_M) {
        p.second *= 5;
        cout << p.first << p.second << endl;
    }

    FuncPtr funcPtr;
    funcPtr = &Hello;
    funcPtr();

    int type = static_cast<int>(WarriorType::KNIGHT);
}
