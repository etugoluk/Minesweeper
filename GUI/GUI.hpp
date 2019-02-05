#pragma once

#include <SFML/Graphics.hpp>
#include "../Logic/Logic.hpp"

constexpr int		imageSize = 50.0;
constexpr int		screenSize = 500;

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