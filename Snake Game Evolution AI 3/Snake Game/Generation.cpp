#include "pch.h"
#include "Generation.h"

Generation::Generation(Grid a_grid)
{
	m_grid = Grid(a_grid.getGridSize());
	m_grid.setFoodPositionVector(a_grid.getFoodPositionVector());
	for (int i = 0; i < m_mutantCount; ++i)
	{
		std::vector<Point2D> newMoveset;
		for (int u = 0; u < m_moveTotal; ++u)
		{
			newMoveset.push_back(getRandomPoint2D());
		}
		Grid newGrid = a_grid;
		m_mutant.push_back(Snake(newMoveset, newGrid));
	}
}

Generation::~Generation()
{
}


Snake Generation::getBestEvolution()
{
	Snake bestSnake = m_mutant[0];
	for (int i = 1; i < m_mutantCount; ++i)
	{
		if (m_mutant[i].getEvolutionScore() > bestSnake.getEvolutionScore()) { bestSnake = m_mutant[i]; }
	}

	//Update Score Limit for overflow
	if (bestSnake.getScore() > 4 + m_scoreLimit)
	{
		m_scoreLimit += bestSnake.getScore() - (4 + m_scoreLimit);
	}

	return bestSnake;
}

void Generation::getNewGeneration(int a_bestSnakeScore)
{
	//Kill off the weak
	int benchmark = a_bestSnakeScore / 2;
	for (int i = m_mutant.size() - 1; i >= 0; --i)
	{
		if (m_mutant[i].getEvolutionScore() < benchmark)
		{
			m_totalScore -= m_mutant[i].getEvolutionScore();
			m_mutant.erase(m_mutant.begin() + i);
		}
	}


	//Set New Children

	//Loop Empty Spaces
	while (m_mutant.size() < m_mutantCount)
	{
		std::vector<Point2D> newMoveset;

		//Loop MoveCount to get a new moveset
		for (int i = 0; i < m_moveTotal; ++i)
		{
			int selectionNum = rand() % m_totalScore;
			int total = 0;

			//Loop Parents to get best move
			for (int u = 0; u < m_mutant.size(); ++u)
			{
				//Get Parent
				total += m_mutant[u].getEvolutionScore();

				if (selectionNum < total)
				{
					//Set Move
					newMoveset.push_back(m_mutant[u].getMoveset()[i]);
					break;
				}
			}
		}

		m_mutant.push_back(Snake(newMoveset, m_grid));
	}

	//Mutation
	for (int i = 0; i < m_mutantCount; ++i)
	{
		for (int u = m_moveTotal - m_baseMoveCount; u < m_moveTotal; ++u)
		{
			if (rand() % m_mutateChance == 0)
			{
				m_mutant[i].setMove(getRandomPoint2D(), u);
			}
		}
	}
	//Reset Snakes
	while (m_mutant.front().getEvolutionScore() > 0)
	{
		m_mutant.push_back(Snake(m_mutant.front().getMoveset(), m_grid));
		m_mutant.erase(m_mutant.begin());
	}

	m_totalScore = 0;
	m_generationCount++;

	if (m_generationCount % m_mutateRound == 0) m_moveTotal += m_generationIncrease;
	for (int i = 0; i < m_mutantCount; ++i)
	{
		for (int u = m_moveTotal; u < m_moveTotal + m_generationIncrease; ++u)
		{
				m_mutant[i].getMoveset().push_back(getRandomPoint2D());
		}
	}
}
int Generation::getMoveTotal()
{
	return m_moveTotal;
}

int Generation::getGenerationCount()
{
	return m_generationCount;
}

void Generation::doTheEvolving()
{
	for (int i = 0; i < m_mutant.size(); ++i)
	{
		for (int u = 0; u < m_moveTotal; ++u)
		{
			if (!m_mutant[i].getDead())
			{
				if (!m_mutant[i].update(m_moveTotal)) m_mutant[i].setDead(true);
			}
			else break;
		}
	}
}

void Generation::countTotalScore()
{
	for (int i = 0; i < m_mutantCount; ++i)
	{
		int num1 = abs((m_grid.getGridSize()*2) - (m_mutant[i].getDistanceToFood()+1));
		int num2 = pwr(10, m_mutant[i].getScore() - m_scoreLimit);
		m_mutant[i].setEvolutionScore( num1 * num2 );
		m_totalScore += m_mutant[i].getEvolutionScore();
	}
}

std::string Generation::drawGeneration()
{
	return "\n-----------------------------------\nGeneration " + std::to_string(m_generationCount) 
			  + "\nTotal Moves: " + std::to_string(m_moveTotal) 
			  + "\nScore Limit: " + std::to_string(m_scoreLimit)
			  + "\n-----------------------------------\n";
}