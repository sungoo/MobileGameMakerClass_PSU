#pragma once
#define CREATURE_NUM 10

class World
{
	Creature* player;
	Creature* computer;
	vector<Creature*> goblins;
	int MonsterLeft;

public:
	enum PlayerType {
		NONE,
		KNIGHT,
		ARCHER,
		MAGE,
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
	void Battle2();

	void MonsterLeftUpdate();

	bool GoblinsClear();
};

