#pragma once
class Barrel
{
	shared_ptr<Line> _line;

	float _barrelLength = 100.0f;
	Vector2 _direction = Vector2(1, 0);

public:
	Barrel();
	Barrel(Vector2 dir, float length);
	~Barrel();

	void Update();
	void Render(HDC hdc);

	void SetStart(Vector2 start);
	void SetAngle(float angle);

	Vector2 GetBarrelEnd();
	Vector2 GetDirection();
};

