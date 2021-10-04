#pragma once
#include "Blocks.h"

class Texture;
class Coin: public Block
{
public:
	Coin(int row, int column);
	~Coin();
	void Draw() const override;
	void Update(float elapsedSec) override;
	virtual bool IsCreatureOverlapping(Mario* marioCollision) const override;
	virtual bool IsDestructibleOnTouch() override;

private:
	float m_Height{14};
	float m_Width{8};
	int m_Score{100};
	Texture* m_pTextureCoin;
	
};

