#pragma once

#include <SFML/Graphics.hpp>
#include "../Logic/Logic.hpp"

constexpr int		imageSize = 50;
constexpr int		screenSize = 500;

class GUI
{
	bool				isFirstClick;
	int					gameStatus;
	int					windowSize;
	int					cellSize;

	sf::RenderWindow	window;
	sf::Text			timer;
	sf::Text			state;
    sf::Font			font;

public:
	GUI(int mapSize);
	~GUI();

	void initText();
	void execute(Logic & logic);
	void check_event(sf::Event const & event, Logic & logic);
	void drawCell(Cell const & cell, int x, int y);
	void drawMap(Cell** map, int size);

	class BadImage: public std::exception {
    public:
        const char* what() const throw();
    };
    
    class BadFont: public std::exception {
    public:
        const char* what() const throw();
    };
};