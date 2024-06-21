#pragma once
#define PLNUM 10

enum PlayerType {
	NONE,
	KNIGHT,
	ARCHER,
	MAGE,
};

class World_Raid
{
	vector<Creature*> players;
	Creature* hopGoblin = nullptr;

public:

	World_Raid();
	~World_Raid();

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

};

