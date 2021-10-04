#pragma once
#include <vector>

class Mario;
class Block;
class Grid
{
public:
	Grid(int rows, int colums);
	Grid(const std::string& filepath);
	~Grid();
	void Draw() const;
	void Update(float elapsedSec);
	void LoadGrid(const std::string& filepath);
	void Collision(Mario* marioCollision);
	bool IsOnGround(Mario* mario);
	Point2f PointOfCoordinate(int column, int row);

private:
	std::vector<std::vector<Block* >> m_Blocks;
	int m_Colums;
	int m_Rows;
};

