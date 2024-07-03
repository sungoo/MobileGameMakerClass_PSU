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
	RightHand();
}

void Player::RightHand()
{
	//�ǽ�
	//������� �̿��ؼ� �̷θ� ��������
	//ã�� ���� _path�� �ִ´�.
	/*while (_pos != Vector2(23, 23))
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
	}*/
	/////////////////////////////////////////////
	enum DIRECT {
		DOWN,
		LEFT,
		UP,
		RIGHT,

		DIR_CNT = 4
	};

	Vector2 pos = _pos;
	_path.push_back(pos);
	Vector2 endPos = Vector2(23, 23);

	DIRECT dir = DIRECT::DOWN;

	Vector2 frontPos[4] =
	{
		Vector2{0,1},//UP
		Vector2{-1,0},//LEFT
		Vector2{0,-1},//DOWN
		Vector2{1,0}//RIGHT
	};

	while (true)
	{
		if (pos == endPos)
			break;

		//% �˰����� ��ȯ������ ���� ���δ�.
		int newDir = (dir - 1 + DIRECT::DIR_CNT) % DIRECT::DIR_CNT;
		Vector2 oldDirVector2 = frontPos[dir];
		Vector2 newDirVector2 = frontPos[newDir];

		Vector2 oldPos = pos + oldDirVector2;
		Vector2 newPos = pos + newDirVector2;
		//���������� �� �� ������ ������ �ٲٰ� ���������� ����
		if (Cango(newPos._y, newPos._x)) {
			dir = static_cast<DIRECT>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}
		//������ �� �� ������ ������ �����ϰ� ����
		else if (Cango(oldPos._y, oldPos._x)) {
			pos += oldDirVector2;
			_path.push_back(pos);
		}
		//������ ���� �� ���������� �������� ȸ��
		else {
			dir = static_cast<DIRECT>((dir + 1 + DIR_CNT) % DIR_CNT);
		}
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
