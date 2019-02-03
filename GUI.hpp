#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Logic.hpp"

class GUI
{
	bool isFirstClick;
	int windowSize;
	int cellSize;
	sf::RenderWindow window;

public:
	GUI();
	~GUI();

	void drawCell(Cell const & cell, int x, int y);
	void drawMap(Cell** map, int size);
	void execute(Logic & logic);
};