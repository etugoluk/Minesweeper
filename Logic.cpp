#include "Logic.hpp"
#include <unistd.h>
#include <cstdlib>
#include <iostream>

Logic::Logic(int size) : size(size), bombSize(size)
{
	srand(unsigned(std::time(0)));
	createMap();
}

Logic::~Logic()
{
	destroyMap();
}

int  Logic::getSize() const { return size; }

int  Logic::getBombSize() const { return bombSize; }

Cell** Logic::getMap() const { return map; }

void Logic::createMap()
{
	map = new Cell*[size];
	for (int i = 0; i < size; ++i)
	{
		map[i] = new Cell[size];
	}
}

void Logic::generateMap()
{
	generateBombs();
	setCellValues();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (!map[i][j].getIsBomb())
		    	std::cout << map[i][j].getBombsNear() << " ";
		    else
		    	std::cout << "b" << " ";
		}
		std::cout << std::endl;
	}
}

void Logic::destroyMap()
{
	for (int i = 0; i < size; ++i)
	{
		delete [] map[i];
	}
	delete [] map;
}

void Logic::generateBombs()
{
	int x, y;

	for (int i = 0; i < bombSize; ++i)
	{	
	    do
	    {
	        x = rand() % size;
	        y = rand() % size;
	    }
		while (map[x][y].getIsBomb() || map[x][y].getIsVisible());

		map[x][y].setIsBomb(true);
	}
}

int Logic::countBombs(int x, int y)
{
	int count = 0;

	for (int i = x - 1; i <= x + 1; ++i)
	{
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if (i >= 0 && j >= 0 && i < size && j < size
				&& map[i][j].getIsBomb())
					++count;
		}
	}

	return count;
}

void Logic::setCellValues()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (!map[i][j].getIsBomb())
				map[i][j].setBombsNear(countBombs(i, j));
		}
	}
}

void Logic::setVisibleCells(int x, int y)
{
	if (map[x][y].getIsVisible())
		return ;

	map[x][y].setIsVisible(true);

	if (!map[x][y].getIsBomb() && !map[x][y].getBombsNear())
	{
		for (int i = x - 1; i <= x + 1; ++i)
		{
			for (int j = y - 1; j <= y + 1; ++j)
			{
				if (i >= 0 && j >= 0 && i < size && j < size)
					setVisibleCells(i, j);
			}
		}
	}
}

bool Logic::check_state()
{
	if (check_win() || check_lose())
		return true;
	return false;
}

bool Logic::check_win()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (!map[i][j].getIsVisible() && !map[i][j].getIsBomb())
		    	return false;
		}
	}
	std::cout << "YOU ARE THE GOD OF MINESWEEPER!" << std::endl;
	sleep(3);
	return true;
}

bool Logic::check_lose()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (map[i][j].getIsBomb() && map[i][j].getIsVisible())
			{
				std::cout << "LOOSER" << std::endl;
				sleep(3);
		    	return true;
			}
		}
	}
	return false;
}
