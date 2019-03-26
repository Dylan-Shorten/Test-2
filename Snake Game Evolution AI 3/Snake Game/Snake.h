#pragma once
#include <vector>
#include "Grid.h"
#include "Utility.h"
using namespace Utility;

class Snake
{
private:
	std::vector<Point2D> m_snakeBody;
	std::vector<Point2D> m_moveset;
	int m_currentMoveCount = 0;
	int m_score = 0;
	int m_evolutionScore = 0;
	bool m_dead = false;
	Grid m_grid;
	Point2D m_direction = { 0, 1 };

public:
	Snake();
	Snake(std::vector<Point2D> a_moveset, Grid a_grid);
	~Snake();

	std::vector<Point2D> getSnakeBody();
	int getCurrentMoveCount();
	std::vector<Point2D>& getMoveset();
	int getScore();
	int getEvolutionScore();
	bool getDead();
	Grid getGrid();
	int getDistanceToFood();

	void setCurrentMoveCount(int a_currentMoveCount);
	void setMoveset(std::vector<Point2D> a_moveset);
	void setMove(Point2D a_move, int a_position);
	void setEvolutionScore(int a_evolutionScore);
	void setDead(bool a_dead);

	bool update(int a_moveTotal);
	std::string drawScore();
};