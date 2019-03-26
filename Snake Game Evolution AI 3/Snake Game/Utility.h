#pragma once
#include <string>
#include "windows.h"

namespace Utility
{
	struct Point2D
	{
		int row;
		int col;
	};
	inline void colourText(char text, int a_colourValue)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, a_colourValue);

		std::cout << text;

		SetConsoleTextAttribute(hConsole, 7);
	}
	inline int sign(int num)
	{
		num = num > 0 ? num = 1 : num < 0 ? num = -1 : num = 0;
		return num;
	}
	inline int pwr(int num, int pow)
	{
		int newNum = 1;
		for (int i = 0; i < pow; ++i)
		{
			newNum *= num;
		}
		return newNum;
	}
	inline Point2D getRandomPoint2D()
	{
		Point2D point = { (rand() % 3) - 1, (rand() % 3) - 1 };
		if (abs(point.row) + abs(point.col) > 1)
		{
			if (rand() % 2 == 0)
			{
				point.row = 0;
			}
			else point.col = 0;
		}
		return point;
	}
}