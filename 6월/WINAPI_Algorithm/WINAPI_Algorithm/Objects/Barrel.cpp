#include "pch.h"
#include "Barrel.h"

Barrel::Barrel()
{
	_line = make_shared<Line>(Vector2(), Vector2());
	_line->_end = _line->_start + _direction * _barrelLength;
}

Barrel::Barrel(Vector2 dir, float length)
{
	_direction = dir;
	_barrelLength = length;
	_line = make_shared<Line>(Vector2(), Vector2());
	_line->_end = _line->_start + _direction * _barrelLength;
}

Barrel::~Barrel()
{
}

void Barrel::Update()
{
	_line->_end = _line->_start + _direction * _barrelLength;
	_line->Update();
}

void Barrel::Render(HDC hdc)
{
	_line->Render(hdc);
}

void Barrel::SetStart(Vector2 start)
{
	_line->_start = start;
}

void Barrel::SetAngle(float angle)
{
	_direction._x = cosf(angle);
	_direction._y = sinf(angle);
}

Vector2 Barrel::GetBarrelEnd()
{
	return _line->_end;
}

Vector2 Barrel::GetDirection()
{
	return _direction;
}
