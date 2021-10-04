#include "pch.h"
#include "Grid.h"
#include "Blocks.h"
#include <string>
#include <fstream>
#include "Mario.h"
#include "utils.h"
#include "Coin.h"

Grid::Grid(int rows, int colums)
{
	m_Rows = rows;
	m_Colums = colums;

	for (int r = 0; r < rows; r++)
	{
		std::vector<Block*> temp{}; 
		
		for (int c = 0; c < colums; c++)
		{
			temp.push_back(new Block(r,c));
		}
		m_Blocks.push_back(temp);
	}
}

Grid::Grid(const std::string& filepath)
{
	LoadGrid(filepath);
}

Grid::~Grid()
{
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Colums; c++)
		{
			delete m_Blocks[r][c];
			m_Blocks[r][c] = nullptr;
		}
		m_Blocks[r].clear();
	}
	m_Blocks.clear();
}

void Grid::Draw() const
{	
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Colums; c++)
		{
			if (m_Blocks[r][c] != nullptr)
			{
				m_Blocks[r][c]->Draw();
			}
		}
	}
}

void Grid::Update(float elapsedSec)
{
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Colums; c++)
		{
			if (m_Blocks[r][c] != nullptr)
			{
				m_Blocks[r][c]->Update(elapsedSec);
			}
		}
	}
}

void Grid::LoadGrid(const std::string& filepath)
{
	std::ifstream in{ filepath };
	std::string amountOfRows{};
	std::getline(in, amountOfRows);
	m_Rows = std::stoi(amountOfRows);

	std::string amountOfColums{};
	std::getline(in, amountOfColums);
	m_Colums = std::stoi(amountOfColums);

	for (int r = m_Rows - 1; r >= 0; r--)
	{
		std::vector<Block*> tempVector{};
		for (int c = 0; c < m_Colums; c++)
		{
			std::string typeBlock{};
			std::getline(in, typeBlock, (c < m_Colums - 1) ? ' ': '\n');
			if (true)
			{
				int blockType = std::stoi(typeBlock);
				switch (Block::BlockType(blockType))
				{
				case Block::BlockType::dirt:
					tempVector.push_back(new Block(r, c));
					break;
				case Block::BlockType::coin:
					tempVector.push_back(new Coin(r, c));
					break;
				default:
				case Block::BlockType::air:
					tempVector.push_back(nullptr);
					break;
				}
			}
		}
		m_Blocks.push_back(tempVector);
	}
}

void Grid::Collision(Mario* marioCollision)
{
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Colums; c++)
		{
			if (m_Blocks[r][c] != nullptr)
			{
				if (m_Blocks[r][c]->IsCreatureOverlapping(marioCollision))
				{
					if (m_Blocks[r][c]->IsDestructibleOnTouch())
					{
						delete m_Blocks[r][c];
						m_Blocks[r][c] = nullptr;
					}
				}
			}
		}
	}
}

bool Grid::IsOnGround(Mario* mario)
{
	Rectf boundaries = mario->GetBounds();
	for (int r = 0; r < m_Rows; r++)
	{
		for (int c = 0; c < m_Colums; c++)
		{
			if (m_Blocks[r][c] != nullptr)
			{
				if (m_Blocks[r][c]->IsOnGround(boundaries))
				{
					return true;
				}
			}
		}
	}
	return false;
}

Point2f Grid::PointOfCoordinate(int column, int row)
{
	return Point2f(column * Block::GetBlockSize(), row * Block::GetBlockSize());
}
