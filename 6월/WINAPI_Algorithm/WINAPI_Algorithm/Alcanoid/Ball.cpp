#include "pch.h"
#include "Ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::Update()
{
	_col->Update();
	_col->_center += _direction * _speed;
}

void Ball::Render(HDC hdc)
{
	_col->Render(hdc);
}

void Ball::Fire(Vector2 startPOS, Vector2 direction)
{
	_col->_center = startPOS;
	_direction.Normalize();
	_direction = direction;
}

bool Ball::IsOut()
{
	if (_col->_center._x > WIN_WIDTH || _col->_center._x < 0)
		return true;
	if (_col->_center._y > WIN_HEIGHT || _col->_center._y < 0)
		return true;
	return false;
}

void Ball::OutControll()
{
	Vector2 center = _col->_center;
	if (center._x > WIN_WIDTH || center._x < 0) {
		_direction._x *= -1.0f;
	}
	if (center._y > WIN_HEIGHT || center._y < 0) {
		_direction._y *= -1.0f;
	}
}
