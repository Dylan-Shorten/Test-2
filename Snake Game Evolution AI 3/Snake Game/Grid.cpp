#include "pch.h"
#include "Grid.h"

Grid::Grid()
{
}
Grid::Grid(int a_gridSize)
{
	m_gridSize = a_gridSize;
	m_gridPosition = new int[a_gridSize*a_gridSize];
	for (int i = 0; i < a_gridSize*a_gridSize; ++i) { m_gridPosition[i] = 0; }
	for (int i = 0; i < 100; ++i) { m_foodPosition.push_back({ rand() % m_gridSize, rand() % m_gridSize }); }
	updateFood();
}


Grid::~Grid()
{
}



void Grid::setGridPosition(Point2D a_gridPosition, int a_value)
{
	m_gridPosition[(a_gridPosition.row * m_gridSize) + a_gridPosition.col] = a_value;
}

void Grid::setFoodPositionVector(std::vector<Point2D> a_foodPositionVector)
{
	setGridPosition(m_foodPosition[m_foodPositionCount], 0);
	m_foodPosition = a_foodPositionVector;
	setGridPosition(m_foodPosition[m_foodPositionCount], 2);
}

int Grid::getGridSize()
{
	return m_gridSize;
}

int Grid::getGridPosition(Point2D a_gridPosition)
{
	return m_gridPosition[(a_gridPosition.row * m_gridSize) + a_gridPosition.col];
}

Point2D Grid::getFoodPosition()
{
	return m_foodPosition[m_foodPositionCount];
}
std::vector<Point2D> Grid::getFoodPositionVector()
{
	return m_foodPosition;
}

void Grid::updateFood()
{
	setGridPosition(getFoodPosition(), 0);

	m_foodPositionCount++;

	setGridPosition(getFoodPosition(), 2);
}

void Grid::drawGrid(std::vector<Point2D> a_snakeBody)
{
	std::string gridString;
	for (int row = 0; row < m_gridSize; ++row)
	{
		gridString += "\n";

		for (int col = 0; col < m_gridSize; ++col)
		{
			gridString += " ";
			bool bodyDrawn = false;
			for (int i = 0; i < a_snakeBody.size(); ++i)
			{
				if (a_snakeBody[i].row == row && a_snakeBody[i].col == col)
				{
					std::cout << gridString;
					gridString.clear();
					int colour = (i % 7) + 9;
					colourText(char(254), colour);
					bodyDrawn = true;
					break;
				}
			}
			if (!bodyDrawn && getFoodPosition().row == row && getFoodPosition().col == col) gridString += char(149);
			else if (!bodyDrawn) gridString += ".";
		}
	}
	std::cout << gridString;
}