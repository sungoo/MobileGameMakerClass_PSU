#pragma once
class Block:public RectCollider
{
public:
	enum class BlockType
	{
		ABLE,
		DISABLE,
		PLAYER_POS,
	};

	Block();
	~Block();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetPosition(Vector2 pos);

	void SetBlockType(BlockType type);
	BlockType GetBlockType() { return _type; }

private:
	BlockType _type = BlockType::ABLE;

	vector<HBRUSH> _brushes;
};

