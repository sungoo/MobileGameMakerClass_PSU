#pragma once
class Cannon
{
public:
	Cannon();
	Cannon(Vector2 stPOS);
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();

	const shared_ptr<Collider> GetCollider();
	vector<shared_ptr<class Bullet>>& GetBullets() { return _bullets; }

	bool isControlled = false;
private:
	shared_ptr<Collider> _body;
	shared_ptr<class Barrel> _barrel;
	vector<shared_ptr<class Bullet>> _bullets;

	int hp = 10;
	bool isAlive = true;

	int _bulletNum = 3;
	unsigned int _shootCNT = 0;

	float _angle = 0.0f;
};

