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
	void IsOut();
	void OutControll();

	void Reflect(Vector2 directrion);
	void BlockCrash(shared_ptr<class Alca_Block> block);

	void SetCenter(Vector2 pos);

	shared_ptr<Collider> GetCollider();

private:

	shared_ptr<Collider> _col;
	Vector2 _direction = Vector2(0, 1);
	float _speed = 7.0f;
	bool _isActive = false;

	vector<shared_ptr<Collider>> _ray;
};

