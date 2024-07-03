#include "pch.h"
#include "Ball.h"
#include "Alca_Block.h"
#include "Framework/RectCollider.h"

Ball::Ball()
{
	_col = make_shared<CircleCollider>(CENTER, 10);

}

Ball::~Ball()
{
}

void Ball::Update()
{

	_col->Update();

	if (!_isActive)
		return;
	_col->_center += _direction * _speed;
	OutControll();

}

void Ball::Render(HDC hdc)
{
	_col->Render(hdc);

}

void Ball::Fire(Vector2 startPOS, Vector2 direction)
{
	if (_isActive)
		return;

	_col->_center = startPOS;
	_direction.Normalize();
	_direction = direction;
	SetActive(true);
}

void Ball::IsOut()
{
	if (_col->_center._y > WIN_HEIGHT)
		SetActive(false);
}

void Ball::OutControll()
{
	Vector2 center = _col->_center;
	if (center._y > WIN_HEIGHT)
		IsOut();
	if (center._x > WIN_WIDTH || center._x < 0) {
		_direction._x *= -1.0f;
	}
	if (center._y < 0) {
		_direction._y *= -1.0f;
	}
}

void Ball::Reflect(Vector2 directrion)
{
	_direction = directrion;
}

void Ball::BlockCrash(shared_ptr<class Alca_Block> block)
{
	shared_ptr<RectCollider> bl = dynamic_pointer_cast<RectCollider>(block->GetCollider());
	
	float dir_x = _direction._x;
	float dir_y = _direction._y;

	if (!_isActive || block->IsBreaked())
		return;

	bool hitABlock = false;

	if (block->GetCollider()->IsCollision(_col)) {
		block->Hit();
		//블록에 가로로 부딪힘(= 블록의 높이 범위 이내)
		if (_col->_center._y > bl->Top() && _col->_center._y < bl->Bottom() && !hitABlock)
		{
			_direction = Vector2(-dir_x, dir_y);
			hitABlock = true;
		}
		//블록에 세로로 부딪힘(= 블록의 너비 범위 이내)
		if (_col->_center._x < bl->Right() && _col->_center._x > bl->Left() && !hitABlock)
		{
			_direction = Vector2(dir_x, -dir_y);
			hitABlock = true;
		}
		//블록 모서리에 부딪힘
		else {
			if (!hitABlock) {
				_direction = Vector2(-dir_x, -dir_y);
				hitABlock = true;
			}
		}
	}
}

void Ball::SetCenter(Vector2 pos)
{
	_col->_center = pos;
}

shared_ptr<Collider> Ball::GetCollider()
{
	return _col;
}
