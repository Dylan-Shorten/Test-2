#pragma once
#include "Snake.h"
#include "Grid.h"

class Generation
{
private:
	std::vector<Snake> m_mutant;
	const int m_baseMoveCount = 50;
	int m_moveTotal = m_baseMoveCount;
	int m_mutantCount = 500;
	int m_mutateRound = 5;
	int m_mutateChance = 5;
	int m_totalScore = 0;
	int m_scoreLimit = 0;
	int m_generationCount;
	int m_generationIncrease = 5;
	Grid m_grid;

public:
	Generation(Grid a_grid);

	~Generation();

	Snake getBestEvolution();
	void getNewGeneration(int a_bestSnakeScore);
	int getMoveTotal();
	int getGenerationCount();

	void doTheEvolving();
	void countTotalScore();
	std::string drawGeneration();
};