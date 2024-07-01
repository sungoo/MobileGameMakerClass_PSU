#pragma once
#define LIFETIME 20.0f
class Bullet
{
	shared_ptr<Collider> _col;
	Vector2 _direction = Vector2(1, 0);
	float _speed = 11.0f;

	Vector2 _downVector = Vector2();

	bool _isActive = false;
	
	float lifeTime = LIFETIME;

	weak_ptr<class Cannon> _target;

public:
	Bullet();
	~Bullet();

	void Update();
	void Render(HDC hdc);

	void Fire(Vector2 startPOS, Vector2 direction);
	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }
	bool IsOut();
	void OutControll();

	//Attack1
	void Attack_Cannon(shared_ptr<class Cannon> cannon);

	//Attack2
	void Attack_Cannon();
	void SetTarget(shared_ptr<class Cannon> cannon) { _target = cannon; }
};

