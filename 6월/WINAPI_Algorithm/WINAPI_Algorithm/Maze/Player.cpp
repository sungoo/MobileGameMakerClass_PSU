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
	//실습
	//우수법을 이용해서 미로를 끝점까지
	//찾은 점은 _path에 넣는다.
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

		//% 알고리즘이 순환구조에 많이 쓰인다.
		int newDir = (dir - 1 + DIRECT::DIR_CNT) % DIRECT::DIR_CNT;
		Vector2 oldDirVector2 = frontPos[dir];
		Vector2 newDirVector2 = frontPos[newDir];

		Vector2 oldPos = pos + oldDirVector2;
		Vector2 newPos = pos + newDirVector2;
		//오른쪽으로 갈 수 있으면 방향을 바꾸고 오른쪽으로 진행
		if (Cango(newPos._y, newPos._x)) {
			dir = static_cast<DIRECT>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}
		//앞으로 갈 수 있으면 방향을 유지하고 진행
		else if (Cango(oldPos._y, oldPos._x)) {
			pos += oldDirVector2;
			_path.push_back(pos);
		}
		//오른쪽 앞쪽 다 막혀있으면 왼쪽으로 회전
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
			//발자취
			_maze->SetPlayerPos(_pos);
		}

		_pathIndex++;
	}
}
