#pragma once
class Creature
{
protected://맴버변수 // 속성
	string name;
	string major;
	int MaxHP;
	int cur_hp;
	int atk;

public://맴버함수 // 기능
	Creature(string name, string major, int Max_hp, int afk);
	virtual ~Creature();

	virtual void printInfo();

	virtual void Attack(Creature* other) abstract; //순수가상함수
	virtual void Damaged(int amount);

	void PreAttack(Creature* other);

	bool IsDead() { return cur_hp <= 0; }

	string getName();
	string getMajor();
	int getM_hp();
	int getC_hp();
	int getAtk();
};

