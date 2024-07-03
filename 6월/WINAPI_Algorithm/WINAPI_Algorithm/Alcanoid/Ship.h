#pragma once
class Ship
{
public:
	Ship();
	~Ship();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();
	void BallReflect();

	shared_ptr<class Ball> GetBall() { return _ball; }

private:

	shared_ptr<Collider> _body;
	shared_ptr<class Barrel> _shootLine;
	shared_ptr<class Ball> _ball;

	float _angle = -1.57f;
	float _angleChangeSpeed = 0.07f;
	float _speed = 9.0f;

	bool isMoving = false;
};

