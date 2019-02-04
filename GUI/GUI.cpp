#include "GUI.hpp"
#include <iostream>
#include <ctime>

GUI::GUI(int mapSize)
{
	windowSize = 500;
	window.create(sf::VideoMode(windowSize, windowSize + 50), "Minesweeper");
	cellSize = windowSize / mapSize;
	isFirstClick = true;

    font.loadFromFile("font/Courier.dfont");
    timer.setFont(font);
    timer.setFillColor(sf::Color(255, 255, 255));
    timer.setCharacterSize(25);
    timer.setPosition(10, windowSize + 5);

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

    texture.loadFromFile(fileName.c_str());

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(cellSize / imageSize, cellSize / imageSize);
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
    int gameStatus = 0;

	while (window.isOpen() && !gameStatus)
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

        gameStatus = logic.check_state();
        if (gameStatus == 1)
            state.setString("YOU WIN :D");
        else if (gameStatus == -1)
            state.setString("YOU LOSE ._.");
        else
            state.setString("YOU CAN DO IT!");

        window.draw(state);
        window.display();

        if (gameStatus)
            sf::sleep(sf::milliseconds(3000));
    }
}