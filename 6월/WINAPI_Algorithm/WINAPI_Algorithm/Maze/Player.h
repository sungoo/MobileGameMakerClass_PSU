#pragma once

class Maze;
class Block;

class Player
{
public:
	struct Vertex_Djikstra {
		Vector2 pos;
		float g;

		bool operator<(const Vertex_Djikstra& other)const
		{
			return g < other.g;
		}
		bool operator>(const Vertex_Djikstra& other)const
		{
			return g > other.g;
		}
	};

	struct Vertex {
		Vector2 pos;
		float g;
		float h;	//ÈÞ¸®½ºÆ½ ÇÔ¼ö
		float f;	//g + h

		bool operator<(const Vertex& other)const
		{
			return f < other.f;
		}
		bool operator>(const Vertex& other)const
		{
			return f > other.f;
		}
	};

	Player(shared_ptr<Maze> maze);
	~Player();

	void BeginPlay();

	void RightHand();
	void DFS(Vector2 start);
	void BFS(Vector2 start);
	void Djikstra(Vector2 start);
	void AStart(Vector2 start, Vector2 end);

	bool Cango(int y, int x);

	void Update();

	Vector2 GetPosition() { return _pos; }

private:
	Vector2 _pos = { 1, 1 };
	Vector2 _dir = Vector2(0, 1);

	vector<Vector2> _path;
	vector<vector<bool>> _visited;
	int _pathIndex = 0;
	float _time = 0.0f;

	shared_ptr<Maze> _maze;
};

