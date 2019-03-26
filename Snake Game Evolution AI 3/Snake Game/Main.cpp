#include "pch.h"
#include <iostream>
#include "Generation.h"
#include "Grid.h"
#include <ctime>

int main()
{
	srand((unsigned int)time(NULL));

	Grid grid(20);
	Generation generation(grid);

	while (true)
	{
		generation.doTheEvolving();															//All Snakes from the generation play
		generation.countTotalScore();														//Count The Scores of all the snakes
		

		Snake bestEvolution = generation.getBestEvolution();								//Store Best Snake Information
		int bestEvolutionScore = bestEvolution.getEvolutionScore();							//Store Best Snake End Score
		Snake bestSnake = Snake(bestEvolution.getMoveset(), grid);							//Create New Snake with Best Snake info

		//Draw Best Snake
		while (true)
		{
			std::string str;

			if (!bestSnake.update(generation.getMoveTotal())) break;									//Update Snake Movement + Break While loop if snake dies
			system("cls");																				//Clear Screen


			//Draw Grid
			bestSnake.getGrid().drawGrid(bestSnake.getSnakeBody());


			//Output Best Snake + Generation Details
			str += bestSnake.drawScore();																//Best Snake Score
			str += "\nEvolution Score: " + std::to_string(bestEvolutionScore) + "\n";					//Best Evolution Score
			str += "\nFinal Move Count: " + std::to_string(bestEvolution.getCurrentMoveCount()) + "\n"; //Move Count
			str += generation.drawGeneration();															//Generation Count + Total Move Count + Score Limit
			std::cout << str;																			//Output String
			
			Sleep(30);																					//Sleep for 0.03 seconds
		}

		//Evolve The Generation
		generation.getNewGeneration(bestEvolutionScore);
	}
}