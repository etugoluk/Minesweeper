#include "Logic.hpp"
#include <cstdlib>
#include <ctime>

Logic::Logic(int size) : size(size), bombSize(size * 1.5)
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

void Logic::generateMap(int cx, int cy)
{
	generateBombs(cx, cy);
	setCellValues();
}

void Logic::clearMap()
{
	destroyMap();
	createMap();
}

void Logic::destroyMap()
{
	for (int i = 0; i < size; ++i)
	{
		delete [] map[i];
	}
	delete [] map;
}

void Logic::generateBombs(int cx, int cy)
{
	int x, y;

	for (int i = 0; i < bombSize; ++i)
	{	
	    do
	    {
	        x = rand() % size;
	        y = rand() % size;
	    }
		while (map[x][y].getIsBomb() || x == cx || y == cy);

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
	return true;
}
