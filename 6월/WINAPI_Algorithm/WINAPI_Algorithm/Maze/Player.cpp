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
	_pos = { 1,1 };
	_maze->SetPlayerPos(_pos);
	_pos = _maze->GetStartPos();

	_visited = vector<vector<bool>>(MAXCOUNT_Y, vector<bool>(MAXCOUNT_X, false));
	//DFS(_pos);
	//BFS(_pos);
	//Djikstra(_pos);
	AStart(_pos, _maze->GetEndPos());
	//RightHand();
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

void Player::DFS(Vector2 here)
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

	_visited[here._y][here._x] = true;
	_path.push_back(here);
	_maze->SetBlockType(here._y, here._x, Block::BlockType::PLAYER_FOOTAGE);

	for (int i = 0; i < 8; i++) {
		//인접해있는지
		Vector2 there = here + frontPos[i];
		//there가 이미 방문한 곳인지
		if (_visited[there._y][there._x]) continue;
		//there가 갈 수 있는 점인지
		if (!Cango(there._y, there._x)) continue;
		//there가 끝점인지
		if (there == _maze->GetEndPos()) {
			_path.push_back(there);
			break;
		}

		DFS(there);
	}
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

		//지금 큐의 front가 도착점이면
		if (here == endPos)
			break;

		for (int i = 0; i < 8; i++) {
			Vector2 there = here + frontPos[i];

			//there가 갈 수 있는 블럭인지 확인
			if (!Cango(there._y, there._x)) continue;
			
			// there가 방문되어있었는지 확인
			if(discovered[there._y][there._x] == true)
				continue;

			q.push(there);
			_maze->SetBlockType(there._y, there._x, Block::BlockType::PLAYER_FOOTAGE);
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

	vector<vector<Vector2>> parent =
		vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1, -1)));
	vector<vector<int>> best =
		vector<vector<int>>(MAXCOUNT_Y, vector<int>(MAXCOUNT_X, INT_MAX));
	priority_queue<Vertex_Djikstra, vector<Vertex_Djikstra>, greater<Vertex_Djikstra>> pq;

	Vertex_Djikstra startV;
	startV.pos = start;
	startV.g = 0;
	pq.push(startV);

	best[start._y][start._x] = 0;
	parent[start._y][start._x] = start;

	while (true)
	{
		if (pq.empty())break;

		Vertex_Djikstra here = pq.top();
		pq.pop();

		if (here.pos == _maze->GetEndPos())
			break;

		//전에 발견한 곳이 더 좋은 경로일 때
		if (best[here.pos._y][here.pos._x] < here.g)
			continue;
		//다음 경로 탐색
		for (int i = 0; i < 8; i++) {
			Vector2 there = here.pos + frontPos[i];

			if (!Cango(there._y, there._x))
				continue;

			//새 가중치 : 직선 10, 대각선 14
			int newG = 0;
			if (i < 4)
				newG = here.g + 10;
			else
				newG = here.g + 14;

			if (newG >= best[there._y][there._x])
				continue;

			Vertex_Djikstra thereV;
			thereV.pos = there;
			thereV.g = newG;

			pq.push(thereV);
			_maze->SetBlockType(there._y, there._x, Block::BlockType::PLAYER_FOOTAGE);
			best[there._y][there._x] = newG;
			parent[there._y][there._x] = here.pos;

		}
	}

	Vector2 check = _maze->GetEndPos();
	_path.push_back(check);
	while (true)
	{
		if (check == start) break;

		check = parent[check._y][check._x];
		_path.push_back(check);
	}

	std::reverse(_path.begin(), _path.end());
}

void Player::AStart(Vector2 start, Vector2 end)
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

	vector<vector<Vector2>> parent =
		vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1, -1)));
	vector<vector<int>> best =
		vector<vector<int>>(MAXCOUNT_Y, vector<int>(MAXCOUNT_X, INT_MAX));
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	Vertex startV;
	startV.pos = start;
	startV.g = 0;
	startV.h = start.ManhattanDistance(_maze->GetEndPos()) * 10.0f;
	startV.f = startV.g + startV.h;
	pq.push(startV);

	best[start._y][start._x] = startV.f;
	parent[start._y][start._x] = start;

	while (true)
	{
		if (pq.empty())
			break;

		Vertex here = pq.top();
		pq.pop();

		if (here.pos == _maze->GetEndPos())
			break;

		//전에 발견한 곳이 더 좋은 경로일 때
		if (best[here.pos._y][here.pos._x] < here.f)
			continue;
		//다음 경로 탐색
		for (int i = 0; i < 8; i++) {
			Vector2 there = here.pos + frontPos[i];

			if (!Cango(there._y, there._x))
				continue;

			//새 가중치 : 직선 10, 대각선 14
			int newCost = 0;
			if (i < 4)
				newCost = here.g + 10;
			else
				newCost = here.g + 14;

			int h = there.ManhattanDistance(_maze->GetEndPos()) * 10.0f;
			int f = newCost + h;

			if (f >= best[there._y][there._x])
				continue;

			Vertex thereV;
			thereV.pos = there;
			thereV.g = newCost;
			thereV.h = h;
			thereV.f = f;

			pq.push(thereV);
			_maze->SetBlockType(there._y, there._x, Block::BlockType::PLAYER_FOOTAGE);
			best[there._y][there._x] = f;
			parent[there._y][there._x] = here.pos;

		}
	}

	Vector2 check = _maze->GetEndPos();
	_path.push_back(check);
	while (true)
	{
		if (check == start) break;

		check = parent[check._y][check._x];
		_path.push_back(check);
	}

	std::reverse(_path.begin(), _path.end());
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

		_maze->CreateMazeKruskal();
		BeginPlay();

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
