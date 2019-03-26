#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Utility.h"
using namespace Utility;

class Grid
{
private:
	int* m_gridPosition;
	std::vector<Point2D> m_foodPosition;
	int m_foodPositionCount = 0;
	int m_gridSize;

public:
	Grid();
	Grid(int a_gridSize);
	~Grid();

	void setGridPosition(Point2D a_gridPosition, int a_value);
	void setFoodPositionVector(std::vector<Point2D> a_foodPositionVector);

	int getGridSize();
	int getGridPosition(Point2D a_gridPosition);
	Point2D getFoodPosition();
	std::vector<Point2D> getFoodPositionVector();
	void updateFood();
	void drawGrid(std::vector<Point2D> a_snakeBody);
};

