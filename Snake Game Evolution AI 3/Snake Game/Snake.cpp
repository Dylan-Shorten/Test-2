#include "pch.h"
#include "Snake.h"

Snake::Snake()
{
}
Snake::Snake(std::vector<Point2D> a_moveset, Grid a_grid)
{
	m_snakeBody.reserve(3);
	for (int i = 0; i < 3; ++i) m_snakeBody.push_back({ (a_grid.getGridSize() / 2) - 1,  (a_grid.getGridSize() / 2) - 1 });

	m_moveset = a_moveset;
	m_grid = Grid(a_grid.getGridSize());
	m_grid.setFoodPositionVector(a_grid.getFoodPositionVector());
}


Snake::~Snake()
{
}

std::vector<Point2D> Snake::getSnakeBody()
{
	return m_snakeBody;
}

std::vector<Point2D>& Snake::getMoveset()
{
	return m_moveset;
}

int Snake::getEvolutionScore()
{
	return m_evolutionScore;
}

int Snake::getCurrentMoveCount()
{
	return m_currentMoveCount;
}

int Snake::getScore()
{
	return m_score;
}

bool Snake::getDead()
{
	return m_dead;
}

Grid Snake::getGrid()
{
	return m_grid;
}

int Snake::getDistanceToFood()
{
	return (abs(m_snakeBody.back().row - m_grid.getFoodPosition().row) +
			abs(m_snakeBody.back().col - m_grid.getFoodPosition().col));
}


void Snake::setCurrentMoveCount(int a_currentMoveCount)
{
	m_currentMoveCount = a_currentMoveCount;
}

void Snake::setMoveset(std::vector<Point2D> a_moveset)
{
	m_moveset = a_moveset;
}

void Snake::setMove(Point2D a_move, int a_position)
{
	m_moveset[a_position] = a_move;
}

void Snake::setEvolutionScore(int a_evolutionScore)
{
	m_evolutionScore = a_evolutionScore;
}

void Snake::setDead(bool a_dead)
{
	m_dead = a_dead;
}

bool Snake::update(int a_moveTotal)
{
	Point2D newDirection = m_moveset[m_currentMoveCount];
	if (newDirection.row + newDirection.col != 0 && newDirection.row != m_direction.row*-1 && newDirection.col != m_direction.col*-1) { m_direction = newDirection; }


	m_grid.setGridPosition(m_snakeBody.back(), 1);
	m_snakeBody.push_back(Point2D{ m_snakeBody.back().row + m_direction.row, m_snakeBody.back().col + m_direction.col });

	m_grid.setGridPosition(m_snakeBody.front(), 0);
	m_snakeBody.erase(m_snakeBody.begin());
	

	//Check Wall Collision
	if (m_snakeBody.back().row < 0 || m_snakeBody.back().row >= m_grid.getGridSize() || m_snakeBody.back().col < 0 || m_snakeBody.back().col >= m_grid.getGridSize()) return false;

	//Check Body Collision
	if (m_grid.getGridPosition(m_snakeBody.back()) == 1) return false;

	//Check Fruit Collision
	if (m_grid.getGridPosition(m_snakeBody.back()) == 2)
	{
		m_grid.updateFood();
		m_score++;
		m_snakeBody.push_back(m_snakeBody.back());
	}


	m_currentMoveCount++;

	if (m_currentMoveCount == a_moveTotal) return false;

	return true;
}

std::string Snake::drawScore()
{
	return "\nScore: " + std::to_string(m_score) + "\n";
}