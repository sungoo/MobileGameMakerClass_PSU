#include "pch.h"
#include "World.h"

World::World():
	player(nullptr),
	computer(nullptr)
{
	Input();
	Init();
}

World::~World()
{
	if (player != nullptr)
		delete player;
	if (computer != nullptr)
		delete computer;
}

void World::Init()
{
}

void World::SelectPlayer(string name, int num, Creature** creature)
{
	PlayerType pClass = (PlayerType)num;
	switch (pClass)
	{
	case World::NONE:
		cout << "입력이 잘못되었습니다. 다시 입력해주세요." << endl;
		break;
	case World::KNIGHT:
		*creature = new Knight(name, 500, 15);
		break;
	case World::ARCHER:
		*creature = new Archer(name, 300, 30);
		break;
	case World::MAGE:
		*creature = new Mage(name, 200, 20, 50);
		break;
	default:
		cout << "입력이 잘못되었습니다. 다시 입력해주세요." << endl;
		break;
	}
}

void World::Input()
{
	int pNum = 0;
	int comNum = 0;
	string name;

	cout << "이름 입력 : ";
	cin >> name;
	cout << "1~3 까지의 클래스 입력\n1 . Knight\t2 . Archer\n3 . Mage : ";
	cin >> pNum;
	comNum = rand() % 3 + 1;

	SelectPlayer(name, pNum, &player);
	SelectPlayer("computer", comNum, &computer);
}

bool World::End()
{
	if (player->IsDead() || computer->IsDead())
		return true;
	else
		return false;
}

void World::Battle1()
{
	player->Attack(computer);
	computer->Attack(player);
}

void World::Battle2()
{
}
