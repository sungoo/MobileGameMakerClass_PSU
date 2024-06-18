#pragma once
class Creature
{
protected://맴버변수 // 속성
	string name;
	string major;
	int BaseHP;//레벨 1의 기본값
	int MaxHP;
	int cur_hp;
	int BaseATK;//레벨 1의 기본값
	int atk;
	int _giveExp = 10;
	bool isActive;

public://맴버함수 // 기능
	Creature(string name, string major, int Max_hp, int afk);
	virtual ~Creature();

	virtual void Init();

	virtual void printInfo();

	virtual void Attack(Creature* other) abstract; //순수가상함수
	virtual void Damaged(int amount, Creature* attacker = nullptr);

	void PreAttack(Creature* other);

	bool IsDead();
	virtual void Revival();

	string getName();
	string getMajor();
	int getM_hp();
	int getC_hp();
	int getAtk();
};

