#include <iostream>

using namespace std;

//Singleton
// 1. 전역으로 접근이 가능해야 한다.
// 2. 프로그램에 단 하나만 존재해야 한다.
// 3. 동적할당 되어야 한다.(포인터만 Data 영역에, 정보 자체는 Heap에..)
//

class SoundManager {

	static SoundManager* instance;

	string warriorSound = "워리어 등장!!";
	string archerSound = "아처 등장!!";
private:
	SoundManager(){}
	~SoundManager(){}

public:
	//private에 접근할 수 있는 방법 : public 맴버함수
	static void Create() {
		if(instance == nullptr)
			instance = new SoundManager();
	}
	static void Delete() {
		if (instance != nullptr)
			delete instance;
	}

	static SoundManager* GetInstance() {
		if (instance != nullptr)
			return instance;
		return nullptr;
	}

	void PrintAllSound() {
		cout << warriorSound << endl;
		cout << archerSound << endl;
	}
	void PrintWarriorSound() {
		cout << warriorSound << endl;
	}
};
SoundManager* SoundManager::instance = nullptr;

class Warrior
{
public:
	Warrior() { SoundManager::GetInstance()->PrintWarriorSound(); }
	~Warrior();

private:

};

int main() {
	SoundManager::Create();//가장 처음 생성해서 가장 나중에 삭제

	Warrior* warrior = new Warrior();

	delete warrior; //참조된 횟수가 적은것 부터 삭제
	SoundManager::Delete();

	return 0;
}