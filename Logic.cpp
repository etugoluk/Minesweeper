#include "Logic.hpp"
#include <unistd.h>
#include <ctime>
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

int  Logic::getSize() const
{
	return size;
}

int  Logic::getBombSize() const
{
	return bombSize;
}

Cell** Logic::getMap() const
{
	return map;
}

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

	if (x - 1 >= 0 && y - 1 >= 0 && map[x - 1][y - 1].getIsBomb())
		++count;
	if (x - 1 >= 0 && map[x - 1][y].getIsBomb())
		++count;
	if (x - 1 >= 0 && y + 1 < size && map[x - 1][y + 1].getIsBomb())
		++count;
	if (y - 1 >= 0 && map[x][y - 1].getIsBomb())
		++count;
	if (y + 1 < size && map[x][y + 1].getIsBomb())
		++count;
	if (x + 1 < size && y - 1 >= 0 && map[x + 1][y - 1].getIsBomb())
		++count;
	if (x + 1 < size && map[x + 1][y].getIsBomb())
		++count;
	if (x + 1 < size && y + 1 < size && map[x + 1][y + 1].getIsBomb())
		++count;

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