#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 startPOS, Vector2 direction);
	void SetActive(bool isActive) { _isActive = isActive; }
	bool IsActive() { return _isActive; }
	bool IsOut();
	void OutControll();
private:

	shared_ptr<Collider> _col;
	Vector2 _direction = Vector2(0, 1);
	float _speed = 11.0f;
	bool _isActive = false;


};

