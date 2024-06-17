#pragma once
#define CREATURE_NUM 10

class World
{
	Creature* player;
	Creature* computer;
	//나중엔 몬스터 묶음만 따로 만들고 처리하는 클래스를 만드는게 좋을듯..
	Creature* goblins;
	int MonsterLeft;

public:
	enum PlayerType {
		NONE,
		KNIGHT,
		ARCHER,
		MAGE,
		GOBLINE,
	};

	World();
	~World();
	//깊은 복사 : 복사 생성자 / 복사 대입연산자
	//이후 구현 필요
	//World(const World& other);
	//World& operator=(const World& other);

	void Init();

private:
	void SelectPlayer(string name, int num, Creature** creature);
	void Input();
public:
	int End();
	void Run(int choose);

	void PrintPlayerInfo();
	void PrintCpuInfo();
	void PrintMonsterInfo(int it);

	void Battle1();
	void Battle2();//과제

	void MonsterLeftUpdate();
	bool GoblinsClear();
};

