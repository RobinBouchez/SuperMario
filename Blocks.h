#pragma once
class Texture;
class Mario;
class Block
{
public:

	Block(int row, int column);
	~Block(); 
	virtual void Draw() const;
	virtual void Update(float elapsedSec);
	enum class BlockType: int
	{
		air = 0,
		dirt = 1, coin = 2
	};
	virtual bool IsCreatureOverlapping( Mario* marioCollision) const;
	bool IsOnGround(const Rectf& creature) const;
	bool CollisionRightSide(Rectf& creature) const;
	bool CollisionLeftSide(Rectf& creature) const;
	bool CollisionGround(Rectf& creature) const;
	static float GetBlockSize();
	virtual bool IsDestructibleOnTouch();

protected:
	int m_Row;
	int m_Column;
	static float m_BlockSize;	
	Texture* m_pTextureDirt;
	
};


