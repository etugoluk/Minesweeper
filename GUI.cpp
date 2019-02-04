#include "GUI.hpp"
#include <iostream>
#include <ctime>

GUI::GUI()
{
	windowSize = 500;
	window.create(sf::VideoMode(windowSize, windowSize + 50), "Minesweeper");
	cellSize = 50;
	isFirstClick = true;
    isGame = true;

    font.loadFromFile("font/Courier.dfont");
    timer.setFont(font);
    timer.setFillColor(sf::Color(255, 255, 255));
    timer.setCharacterSize(25);
    timer.setPosition(5, windowSize + 5);

    state.setFont(font);
    state.setFillColor(sf::Color(255, 255, 255));
    state.setCharacterSize(25);
    state.setPosition(200, windowSize + 5);
}

GUI::~GUI(){
    window.clear();
    window.close();
}

void GUI::drawCell(Cell const & cell, int x, int y)
{
	sf::Texture texture;
    std::string fileName;

	if (cell.getIsMarked())
        fileName = "img/flaged.png";
	else if (!cell.getIsVisible())
    	fileName = "img/closed.png";
    else if (cell.getIsVisible() && cell.getIsBomb())
    	fileName = "img/bomb.png";
    else
        fileName = "img/num" + std::to_string(cell.getBombsNear()) + ".png";

    texture.loadFromFile(fileName.c_str(), sf::IntRect(0, 0, cellSize, cellSize));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(y * cellSize, x * cellSize);
	window.draw(sprite);
}

void GUI::drawMap(Cell** map, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			drawCell(map[i][j], i, j);
		}
	}
}

void GUI::execute(Logic & logic)
{
	Cell** map = logic.getMap();
    std::clock_t start = std::clock();

	while (window.isOpen() && isGame)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
        	if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.x < 500 && event.mouseButton.y < 500)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if (map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsMarked())
                        map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].setIsMarked(false);
                    else if (!map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsVisible())
                       map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].setIsMarked(true);
                }
                else if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isFirstClick)
                    {
                        logic.generateMap(event.mouseButton.y / cellSize, event.mouseButton.x / cellSize);
                        isFirstClick = false;
                    }
                    if (!map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsVisible())
                        logic.setVisibleCells(event.mouseButton.y / cellSize, event.mouseButton.x / cellSize);
                }
            }
        }

        window.clear();
        drawMap(logic.getMap(), logic.getSize());
        timer.setString("Time: " + std::to_string(static_cast<int>((std::clock() - start )/CLOCKS_PER_SEC)));
        window.draw(timer);

        switch (logic.check_state())
        {
            case 1:
                state.setString("YOU WIN :D");
                window.draw(state);
                isGame = false;
                break;
            case -1:
                state.setString("YOU LOSE ._.");
                window.draw(state);
                isGame = false;
                break;
        }

        window.display();
    }
}