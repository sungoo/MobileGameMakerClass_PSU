#pragma once
class Creature
{
protected://맴버변수 // 속성
	string name;
	int MaxHP;
	int cur_hp;
	int atk;

public://맴버함수 // 기능
	Creature(string name, int Max_hp, int afk);
	virtual ~Creature();

	void printInfo();

	virtual void Attack(Creature* other) abstract; //순수가상함수
	virtual void Damaged(int amount);

	void PreAttack(Creature* other);

	bool IsDead() { return cur_hp <= 0; }
};

