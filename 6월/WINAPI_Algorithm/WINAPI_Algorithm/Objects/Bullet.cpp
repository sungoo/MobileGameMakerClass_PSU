#include "pch.h"
#include "Bullet.h"
#include "Cannon.h"

void Bullet::SetActive(bool isActive)
{
	_isActive = isActive;
}

bool Bullet::IsOut()
{
	if (_col->_center._x > WIN_WIDTH || _col->_center._x < 0)
		return true;
	if (_col->_center._y > WIN_HEIGHT || _col->_center._y < 0)
		return true;
	return false;
}
//벽에 맞으면 튕기게 하기
void Bullet::OutControll()
{
	Vector2 center = _col->_center;
	if (center._x > WIN_WIDTH || center._x < 0) {
		_direction._x *= -1.0f;
	}
	if (center._y > WIN_HEIGHT || center._y < 0) {
		_direction._y *= -1.0f;
	}
}

void Bullet::Attack_Cannon(shared_ptr<class Cannon> cannon)
{
	if (!_isActive)
		return;
	if (cannon->GetCollider()->IsCollision(_col)) {
		cannon->GetCollider()->SetRed();

		SetActive(false);
	}
}

void Bullet::Attack_Cannon()
{
	if (_target.expired() == false) {
		if (_target.lock()->GetCollider()->IsCollision(_col)) {
			SetActive(false);
		}
	}
}

Bullet::Bullet()
{
	_col = make_shared<CircleCollider>(CENTER, 7);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!_isActive) return;

	Attack_Cannon();

	_col->Update();
	_col->_center += _direction * _speed;

	//TODO : 중력 작용
	//_col->_center += _downVector;
	//_downVector += Vector2(0, 1) * GRAVITY;

	//TODO : 화면 밖으로 나갔을 때 사라짐
	//outControll : 반사를 위한 함수
	OutControll();
	lifeTime -= 0.1f;
	if (lifeTime < 0.0f /* || IsOut()*/) {
		_isActive = false;
		lifeTime = LIFETIME;
	}
}

void Bullet::Render(HDC hdc)
{
	if (!_isActive) return;

	_col->Render(hdc);
}

void Bullet::Fire(Vector2 startPOS, Vector2 direction)
{
	if (_isActive) return;

	if (!_isActive)
		SetActive(true);
	_col->_center = startPOS;
	_direction = direction;
	_direction.Normalize();
	_downVector = Vector2();
}
