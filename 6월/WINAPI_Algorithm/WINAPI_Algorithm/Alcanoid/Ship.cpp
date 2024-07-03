#include "pch.h"
#include "Ship.h"
#include "Objects/Barrel.h"
#include "Ball.h"

Ship::Ship()
{
	_body = make_shared<RectCollider>
		(
			Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT - 100.0f) , 
			Vector2(70.0f, 5.0f)
		);
	_shootLine = make_shared<Barrel>(Vector2(0, -1), 50.0f);
	_ball = make_shared<Ball>();
	_shootLine->SetStart(_body->_center + Vector2(0, -12));
	_ball->SetCenter(_body->_center + Vector2(0, -12));
}

Ship::~Ship()
{
}

void Ship::Update()
{
	_body->Update();
	_shootLine->Update();
	_ball->Update();

	Move();
	Fire();
	BallReflect();

	if (!isMoving) {
		if (_angle > -1.2f)
			_angle -= _angleChangeSpeed;
		if (_angle < -1.94f)
			_angle += _angleChangeSpeed;
	}
}

void Ship::Render(HDC hdc)
{
	_body->Render(hdc);
	//_shootLine->Render(hdc);
	_ball->Render(hdc);
}

void Ship::Move()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		isMoving = true;
		_body->_center._x += _speed;
		if (_angle <= -0.27f) {
			if (_angle < -1.57f)
				_angle += _angleChangeSpeed * 3;
			else
				_angle += _angleChangeSpeed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) == 0) {
		isMoving = false;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		isMoving = true;
		_body->_center._x -= _speed;
		if (_angle >= -2.87f) {
			if (_angle > -1.57f)
				_angle -= _angleChangeSpeed * 3;
			else
				_angle -= _angleChangeSpeed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		isMoving = false;
	}

	_shootLine->SetAngle(_angle);
	_shootLine->SetStart(_body->_center + Vector2(0, -12));
	if(!_ball->IsActive())
		_ball->SetCenter(_body->_center + Vector2(0, -12));
}

void Ship::Fire()
{
	if (_ball->IsActive())
		return;

	if (GetAsyncKeyState(VK_SPACE)) {
		_ball->Fire(_body->_center + Vector2(0, -12), _shootLine->GetDirection());
	}
}

void Ship::BallReflect()
{
	if (!_ball->IsActive())
		return;

	if (_ball->GetCollider()->IsCollision(_body))
		_ball->Reflect(_shootLine->GetDirection());
}
