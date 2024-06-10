#pragma once
class World
{
	Creature* player;
	Creature* computer;

public:
	enum PlayerType {
		NONE,
		KNIGHT,
		ARCHER,
		MAGE,
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
	bool End();

	void Battle1();
	void Battle2();//과제
};

