#pragma once

#include <SFML/Graphics.hpp>
#include "../Logic/Logic.hpp"

constexpr double imageSize = 50.0;

class GUI
{
	bool				isFirstClick;
	int					windowSize;
	int					cellSize;
	sf::RenderWindow	window;
	sf::Text			timer;
	sf::Text			state;
    sf::Font			font;

public:
	GUI(int mapSize);
	~GUI();

	void drawCell(Cell const & cell, int x, int y);
	void drawMap(Cell** map, int size);
	void execute(Logic & logic);
};