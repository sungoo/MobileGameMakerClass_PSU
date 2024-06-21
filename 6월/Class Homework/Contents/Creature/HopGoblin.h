#pragma once
#include "Monster.h"

struct DamageTable {
	//매 턴 데미지
	int _Damage = 0;
	//누적 데미지
	int _Total = 0;

	Creature* _who = nullptr;

	DamageTable(int dmg, Creature* newbe);
};
class HopGoblin :public Monster
{
	//플레이어별 누적 데미지
	vector<DamageTable*> _DamageRate;

	struct CompDamageTable {
		bool operator()(const DamageTable* a, const DamageTable* b);
	};

public:
	HopGoblin(string name, string major, int hp, int atk, int exp);
	virtual ~HopGoblin();

	//한 번에 네 명의 플레이어 공격
	void Attack(vector<Creature*> others);
	//플레이어 각자가 불러올 공격 함수
	void SingleDamaged(int amount, Creature* attacker);
	//공격을 모두 모아 총 데미지 처리
	void Damaged();

	void PreAttack(vector<Creature*> others);
};

