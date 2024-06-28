#pragma once

class HResult;

class Line
{
public:
	Line(Vector2 start, Vector2 end);
	~Line();

	void Update();
	void Render(HDC hdc);

	HResult IsCollision(shared_ptr<Line> other);

	void SetRed() { _curpen = _pens[0]; }
	void SetGreen() { _curpen = _pens[1]; }

public:

	vector<HPEN> _pens;
	HPEN _curpen;

	Vector2 _start;
	Vector2 _end;
};

