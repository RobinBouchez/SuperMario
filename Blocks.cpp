#include "pch.h"
#include "Blocks.h"
#include "utils.h"
#include "Mario.h"
#include "Texture.h"

float Block::m_BlockSize = 25;
Block::Block(int row, int column)
{
	m_Row = row;
	m_Column = column;
	m_pTextureDirt = new Texture{ "Resources/Dirt.png" };
}

Block::~Block()
{
	delete m_pTextureDirt;
	m_pTextureDirt = nullptr;
}

void Block::Draw() const
{
	m_pTextureDirt->Draw(Rectf{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize });
	//utils::SetColor(Color4f{ 1,0,0,1 });
	//utils::DrawRect(m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize);
}

void Block::Update(float elapsedSec)
{

}

bool Block::IsCreatureOverlapping(Mario* marioCollision) const
{
	Rectf creature = marioCollision->GetBounds();
	bool isOverlapping = false;
	isOverlapping = isOverlapping || CollisionGround(creature);
	isOverlapping = isOverlapping || CollisionLeftSide(creature);
	isOverlapping = isOverlapping || CollisionRightSide(creature);
	marioCollision->SetBounds(creature);
	return isOverlapping;
}

bool Block::IsOnGround(const Rectf& creature) const
{
	Rectf blockBound{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize };
	Point2f upLeft(m_Column * m_BlockSize, m_Row * m_BlockSize + m_BlockSize);
	Point2f upRight{ m_Column * m_BlockSize + m_BlockSize, m_Row * m_BlockSize + m_BlockSize };
	Point2f creatureMiddle{ (creature.left + creature.width / 2), (creature.bottom + creature.height / 2) };
	Point2f creatureBottom{ (creature.left + creature.width / 2), (creature.bottom - 2) };
	utils::HitInfo info{};

	return (utils::Raycast({ upLeft,upRight }, creatureMiddle, creatureBottom, info));
}

bool Block::CollisionRightSide(Rectf& creature) const
{
	Rectf blockBound{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize };
	Point2f upRight{ m_Column * m_BlockSize + m_BlockSize, m_Row * m_BlockSize + m_BlockSize };
	Point2f downRight{ m_Column * m_BlockSize + m_BlockSize, m_Row * m_BlockSize };
	Point2f creatureMiddle{ (creature.left + creature.width / 2), (creature.bottom + creature.height / 2) };
	Point2f CreatureLeft{ (creature.left - 2),(creature.bottom + creature.height / 2) };
	utils::HitInfo info{};

	if (utils::Raycast({ upRight, downRight }, creatureMiddle, CreatureLeft, info))
	{
		creature.left = info.intersectPoint.x; //- creature.width;
	}
	return utils::IsOverlapping(creature, blockBound);
}

bool Block::CollisionLeftSide(Rectf& creature) const
{
	Rectf blockBound{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize };
	Point2f upLeft(m_Column * m_BlockSize, m_Row * m_BlockSize + m_BlockSize);
	Point2f downLeft{ m_Column * m_BlockSize, m_Row * m_BlockSize};
	Point2f creatureMiddle{ (creature.left + creature.width / 2), (creature.bottom + creature.height / 2) };
	Point2f CreatureRight{ (creature.left + creature.width + 2),(creature.bottom + creature.height / 2) };
	utils::HitInfo info{};

	if (utils::Raycast({ upLeft,downLeft }, creatureMiddle, CreatureRight, info))
	{
		creature.left = info.intersectPoint.x - creature.width;
	}
	return utils::IsOverlapping(creature, blockBound);
}

bool Block::CollisionGround(Rectf& creature) const
{
	Rectf blockBound{ m_Column * m_BlockSize, m_Row * m_BlockSize, m_BlockSize, m_BlockSize };
	Point2f upLeft(m_Column * m_BlockSize, m_Row * m_BlockSize + m_BlockSize);
	Point2f upRight{ m_Column * m_BlockSize + m_BlockSize, m_Row * m_BlockSize + m_BlockSize };
	Point2f creatureMiddle{ (creature.left + creature.width / 2), (creature.bottom + creature.height / 2) };
	Point2f creatureBottom{ (creature.left + creature.width / 2), (creature.bottom - 2) };
	utils::HitInfo info{};
	if (utils::Raycast({ upLeft,upRight }, creatureMiddle, creatureBottom, info))
	{
		creature.bottom = info.intersectPoint.y;
	}
	return (utils::Raycast({ upLeft,upRight }, creatureMiddle, creatureBottom, info));
}

float Block::GetBlockSize()
{
	return m_BlockSize;
}

bool Block::IsDestructibleOnTouch()
{
	return false;
}
