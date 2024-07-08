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
	_pos = _maze->GetStartPos();
	DFS(_pos);
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
	Vector2 endPos = _maze->GetEndPos();

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

	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++) {

		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}
	s.push(_path.back());

	_path.clear();

	while (true)
	{
		if (s.empty() == true)
			break;

		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::DFS(Vector2 start)
{
	Vector2 frontPos[8] =
	{
		Vector2{0,1},//UP
		Vector2{-1,0},//LEFT
		Vector2{0,-1},//DOWN
		Vector2{1,0},//RIGHT

		Vector2{-1,1},//UP-LEFT
		Vector2{-1,-1},//LEFT-BOTTOM
		Vector2{1,1},//BOTTOM-RIGHT
		Vector2{1,-1}//RIGHT-UP
	};

	vector<vector<bool>> discovered = vector<vector<bool>>(MAXCOUNT_Y, vector<bool>(MAXCOUNT_X, false));

	Vector2 pos = start;
	Vector2 endPos = _maze->GetEndPos();

	discovered[start._y][start._x] = true;

	stack<Vector2> s;
	s.push(start);

	while (true)
	{
		if (s.empty()) break;

		Vector2 here = s.top();
		s.pop();

		//���� ������ top�� �������̸�
		if (here == endPos)
			break;

		for (int i = 0; i < 4; i++) {
			Vector2 there = here + frontPos[i];

			//there�� �� �� �ִ� ������ Ȯ��
			if (!Cango(there._y, there._x)) continue;

			// there�� �湮�Ǿ��־����� Ȯ��
			if (discovered[there._y][there._x] == true)
				continue;

			s.push(there);
			discovered[there._y][there._x] = true;
		}
	}

	Vector2 check = endPos;
	_path.push_back(check);
	while (true)
	{
		if (s.empty()) break;
		if (check == start) break;

		check = s.top();
		_path.push_back(check);
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::BFS(Vector2 start)
{
	Vector2 frontPos[8] =
	{
		Vector2{0,1},//UP
		Vector2{-1,0},//LEFT
		Vector2{0,-1},//DOWN
		Vector2{1,0},//RIGHT

		Vector2{-1,1},//UP-LEFT
		Vector2{-1,-1},//LEFT-BOTTOM
		Vector2{1,1},//BOTTOM-RIGHT
		Vector2{1,-1}//RIGHT-UP
	};

	vector<vector<bool>> discovered = vector<vector<bool>>(MAXCOUNT_Y, vector<bool>(MAXCOUNT_X, false));
	vector<vector<Vector2>> parent = vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1, -1)));
	
	Vector2 pos = start;
	Vector2 endPos = _maze->GetEndPos();

	discovered[start._y][start._x] = true;
	parent[start._y][start._x] = start;

	queue<Vector2> q;
	q.push(start);

	while (true)
	{
		if (q.empty()) break;

		Vector2 here = q.front();
		q.pop();

		//���� ť�� front�� �������̸�
		if (here == endPos)
			break;

		for (int i = 0; i < 8; i++) {
			Vector2 there = here + frontPos[i];

			//there�� �� �� �ִ� ������ Ȯ��
			if (!Cango(there._y, there._x)) continue;
			
			// there�� �湮�Ǿ��־����� Ȯ��
			if(discovered[there._y][there._x] == true)
				continue;

			q.push(there);
			discovered[there._y][there._x] = true;
			parent[there._y][there._x] = here;
		}
	}

	Vector2 check = endPos;
	_path.push_back(check);
	while (true)
	{
		if(check == start) break;

		check = parent[check._y][check._x];
		_path.push_back(check);
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::Djikstra(Vector2 start)
{
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
