#pragma once
class Player : public Creature
{
protected:
	int _currExp = 0;
	int _Lv = 1;

public:
	Player(string name, string major, int hp, int afk);
	Player(string name, string major, int hp, int afk, int Lv);
	virtual ~Player();

	void GainExp(int much);
	void LevelUp();
	void UpdateStatue();
	virtual void Revival();//부활시키기

	void MultiAttack(vector<Creature*> arr, int size);
};

