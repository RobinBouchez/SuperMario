#include "pch.h"
#include "Coin.h"
#include "utils.h"
#include "Texture.h"
#include "Mario.h"

Coin::Coin(int row, int column)
	:Block{row, column}
{
	m_pTextureCoin = new Texture("Resources/Coin.png");
}

Coin::~Coin()
{
	delete m_pTextureCoin;
	m_pTextureCoin = nullptr;
}

void Coin::Draw() const
{
	m_pTextureCoin->Draw(Rectf{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize });
}

void Coin::Update(float elapsedSec) 
{

}

bool Coin::IsCreatureOverlapping(Mario* marioCollision) const
{
	Rectf blockBound{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize };
	bool isOverlapping = utils::IsOverlapping(marioCollision->GetBounds(), blockBound);
	if (isOverlapping)
	{
		marioCollision->AddScore(m_Score);
	}
	return isOverlapping;
}

bool Coin::IsDestructibleOnTouch()
{
	return true;
}
