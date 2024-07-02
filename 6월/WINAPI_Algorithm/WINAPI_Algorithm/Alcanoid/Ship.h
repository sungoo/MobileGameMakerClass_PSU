#pragma once
class Ship
{
public:
	Ship();
	~Ship();

	void Update();
	void Render(HDC hdc);

	void Move();

private:

	shared_ptr<Collider> _body;
	shared_ptr<class Barrel> _shootLine;

	float _angle = -1.57f;
	float _angleChangeSpeed = 0.03f;
	float _speed = 5.0f;

	bool isMoving = false;
};

