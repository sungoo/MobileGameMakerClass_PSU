#pragma once
#define MAXWIDTHCNT 12
#define MAXHIGHTCNT 5

class AlcanoidScene: public Scene
{
public:
	AlcanoidScene();
	~AlcanoidScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<class Ship> _player;
	vector<vector<shared_ptr<class Alca_Block>>> _blocks;
};

