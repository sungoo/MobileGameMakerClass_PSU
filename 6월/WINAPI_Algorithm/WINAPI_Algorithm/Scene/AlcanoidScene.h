#pragma once
class AlcanoidScene: public Scene
{
public:
	AlcanoidScene();
	~AlcanoidScene();

	void Update() override;
	void Render(HDC hdc) override;

private:
	shared_ptr<class Ship> _player;
};

