#pragma once
#define CREATURE_NUM 10

class World
{
	Creature* player;
	Creature* computer;
	//나중엔 몬스터 묶음만 따로 만들고 처리하는 클래스를 만드는게 좋을듯..
	Creature* goblin;

	vector<Creature*> goblins;
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
	
	void Init();
	void ResetCPU();
private:
	void SelectPlayer(string name, int num, Creature** creature);
	int Input();
	
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

