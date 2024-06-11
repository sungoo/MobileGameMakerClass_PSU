#pragma once



class Player
{
public:
	Player();
	Player(int hp);

	virtual ~Player();
	
	// 정보를 출력하는 함수입니다.
	// 추가 정보가 있다면 override해서 사용하세요~
	virtual void PrintInfo();

	virtual void AddHp(int value);
	bool IsDead();

	int GetAttackDamage();

	void OnDamaged(Player* attacker);

public:

	int _hp;
	int _maxHp;
	int _attack;
};

