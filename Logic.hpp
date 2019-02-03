#pragma once

#include "Cell.hpp"

class Logic
{
	int size;
	int bombSize;
	Cell **map;
public:
	Logic(int size);
	~Logic();

	int  getSize() const;
	int  getBombSize() const;
	Cell** getMap() const;

	void createMap();
	void generateMap();
	void destroyMap();
	void generateBombs();
	void setCellValues();
	int  countBombs(int x, int y);
};