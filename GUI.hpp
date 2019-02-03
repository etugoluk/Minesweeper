#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Logic.hpp"

class GUI
{
	bool isFirstClick;
	int windowSize;
	int cellSize;
	std::array<sf::Image, 8> numbers;
public:
	sf::RenderWindow window;
	GUI();
	~GUI();

	void initImages();
	void drawCell(Cell const & cell, int x, int y);
	void drawMap(Cell** map, int size);
	void execute(Logic & logic);
};