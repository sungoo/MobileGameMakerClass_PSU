#include "pch.h"
#include "Cannon.h"
#include "Barrel.h"
#include "Bullet.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(CENTER, 50.0f);
	_barrel = make_shared<Barrel>();
	
	for (int i = 0; i < _bulletNum; i++) {
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->SetActive(false);
		_bullets.push_back(bullet);
	}

	Move();
}

Cannon::Cannon(Vector2 stPOS)
{
	_body = make_shared<CircleCollider>(stPOS, 50.0f);
	_barrel = make_shared<Barrel>();

	for (int i = 0; i < _bulletNum; i++) {
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->SetActive(false);
		_bullets.push_back(bullet);
	}

	Move();
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (isControlled) {
		Move();
		Fire();
	}
	
	_body->Update();
	_barrel->Update();
	for (int i = 0; i < _bulletNum; i++)
		_bullets[i]->Update();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
	for (int i = 0; i < _bulletNum; i++)
		_bullets[i]->Render(hdc);
}

void Cannon::Move()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->_center._x += 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->_center._x -= 1.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_angle -= 0.01f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_angle += 0.01f;
	}

	_barrel->SetAngle(_angle);

	_barrel->SetStart(_body->_center);
}

void Cannon::Fire()
{
	//keydown
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		/*if (_bullets[_shootCNT]->IsActive())
			return;

		_bullets[_shootCNT]->Fire(_barrel->GetBarrelEnd(), _barrel->GetDirection());

		if (_shootCNT < _bulletNum - 1)
			_shootCNT++;
		else
			_shootCNT = 0;*/

		auto iter = std::find_if(_bullets.begin(), _bullets.end(),
			[](shared_ptr<Bullet> bullet)->bool {
				if (!bullet->IsActive()) return true;
				return false;
			});

		if (iter != _bullets.end()) {
			(*iter)->Fire(_barrel->GetBarrelEnd(), _barrel->GetDirection());
		}
	}
}

const shared_ptr<Collider> Cannon::GetCollider()
{
	return _body;
}
