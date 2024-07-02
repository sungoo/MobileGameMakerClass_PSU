#include "pch.h"
#include "Player.h"

#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
{
	_maze = maze;
}

Player::~Player()
{
	_maze = nullptr;
}

void Player::BeginPlay()
{
	_maze->SetPlayerPos(_pos);
	FindPath();
}

void Player::FindPath()
{
	//�ǽ�
	//������� �̿��ؼ� �̷θ� ��������
	//ã�� ���� _path�� �ִ´�.
	while (_pos != Vector2(23, 23))
	{
		Vector2 down = { _pos._x, _pos._y + 1 };
		Vector2 right = { _pos._x + 1, _pos._y };
		if (Cango(down._y, down._x)) {
			_pos = down;
			_path.push_back(_pos);
			continue;
		}
		if (Cango(right._y, right._x)) {
			_pos = right;
			_path.push_back(_pos);
			continue;
		}
		break;
	}
}

bool Player::Cango(int y, int x)
{
	Block::BlockType blockType = _maze->GetBlockType(y, x);
	if (blockType == Block::BlockType::ABLE)
		return true;
	return false;
}

void Player::Update()
{
	//FindPath();
	if (_pathIndex >= _path.size()) {
		_pathIndex = 0;
		_path.clear();

		return;
	}
	_time += 0.3f;
	if (_time > 1.0f) {
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex != 0) {
			//������
			_maze->SetPlayerPos(_pos);
		}

		_pathIndex++;
	}
}
