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
	void destroyMap();
	void generateMap(int cx, int cy);
	void clearMap();
	void generateBombs(int cx, int cy);
	void setCellValues();
	int  countBombs(int x, int y);
	void setVisibleCells(int x, int y);
    bool check_win();
};