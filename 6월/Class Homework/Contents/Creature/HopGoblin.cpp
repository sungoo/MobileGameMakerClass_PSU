#include "pch.h"
#include "HopGoblin.h"

HopGoblin::HopGoblin(string name, string major, int hp, int atk, int exp):
	Monster(name, major, hp, atk, exp)
{
	_DamageRate.reserve(10);

	//_DamageRate.resize(10, nullptr);
}

HopGoblin::~HopGoblin()
{
	for (int i = 0; i < _DamageRate.size(); i++) {
		if (_DamageRate[i] != nullptr)
			delete _DamageRate[i];
	}
}

void HopGoblin::Attack(vector<Creature*> others)
{

}

void HopGoblin::SingleDamaged(int amount, Creature* attacker)
{
	//벡터 순회하여 플레이어 정보 탐색
	for (auto it : _DamageRate) {
		if (it->_who == attacker) {
			//같은 플레이어 정보가 이미 있을 때 => damage 변경
			it->_Damage = amount;
			it->_Total += amount;
			//이미 죽은 플레이어의 공격일 때, 
			// 매 턴 데미지는 0으로
			// 누적 데미지에선 제일 끝 위치로 이동.(0으로 만든 후 Sort)
			if (attacker->IsDead()) {
				it->_Damage = 0;
				it->_Total = 0;
			}
			CompDamageTable comp;
			std::sort(_DamageRate.begin(), _DamageRate.end(), comp);
			return;
		}
	}
	//없었던 플레이어의 공격일 때 => 새 플레이어 정보 추가
	DamageTable* newPlayerData = new DamageTable(amount, attacker);
	_DamageRate.push_back(newPlayerData);
}

void HopGoblin::Damaged()
{
	int amount = 0;

	for (auto it : _DamageRate) {
		if (!it->_who->IsDead())
			amount += it->_Damage;
	}

	cur_hp -= amount;

	cout << name << "에게 " << amount << "데미지!!" << endl;

	if (cur_hp < 0)
		cur_hp = 0;

	printInfo();

	if (IsDead()) {
		cout << name << "이 사망했습니다." << endl;
	}
}

void HopGoblin::PreAttack(vector<Creature*> others)
{
}

bool HopGoblin::CompDamageTable::operator()(const DamageTable* a, const DamageTable* b)
{
	return a->_Total > b->_Total;
}

DamageTable::DamageTable(int dmg, Creature* newbe):
	_Damage(dmg), _Total(dmg), _who(newbe)
{
}
