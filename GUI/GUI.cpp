#include "GUI.hpp"
#include <iostream>
#include <ctime>

GUI::GUI(int mapSize)
{
    cellSize = screenSize / mapSize;
    windowSize = cellSize * mapSize;
	window.create(sf::VideoMode(windowSize, windowSize + 50), "Minesweeper");

	isFirstClick = true;
    gameStatus = 0;

    initText();
}

GUI::~GUI(){
    window.clear();
    window.close();
}

void GUI::initText()
{
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
    sprite.setScale(static_cast<double>(cellSize) / imageSize, static_cast<double>(cellSize) / imageSize);
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

void GUI::check_event(sf::Event const & event, Logic & logic)
{
    Cell** map = logic.getMap();

    if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
        window.close();
    else if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.x < windowSize && event.mouseButton.y < windowSize)
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

void GUI::execute(Logic & logic)
{
    std::clock_t start = std::clock();

	while (window.isOpen() && !gameStatus)
    {
        sf::Event event;
        while (window.pollEvent(event))
            check_event(event, logic);

        window.clear();

        //draw Map
        drawMap(logic.getMap(), logic.getSize());

        //draw Timer
        timer.setString("Time: " + std::to_string(static_cast<int>((std::clock() - start )/CLOCKS_PER_SEC)));
        window.draw(timer);

        //draw Game status
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