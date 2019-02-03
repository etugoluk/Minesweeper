#include "GUI.hpp"
#include <iostream>
GUI::GUI()
{
	windowSize = 500;
	window.create(sf::VideoMode(windowSize, windowSize), "Minesweeper");
	cellSize = 50;
	isFirstClick = true;
}

GUI::~GUI(){
    window.clear();
    window.close();
}

void GUI::initImages()
{
	for (int i = 0; i < 8; ++i)
	{
		// std::string fileName = "img/num" + i + 1 + ".png";
		std::string fileName = i + 1 + ".png";
		numbers[i].loadFromFile(fileName.c_str());
	}
	// sf::Image img;
	// img.loadFromFile("img/bomb.png");
	// images.push_back(img);
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
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        	if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    // if (map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsMarked())
                    //     map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].setIsMarked(false);
                    if (!map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsVisible())
			            map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].setIsMarked(true);
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
				    logic.getMap()[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].setIsVisible(true);
                    if (isFirstClick)
                    {
                        logic.generateMap();
                        isFirstClick = false;
                    }
                }
            }
        }
        window.clear();
        drawMap(logic.getMap(), logic.getSize());
        window.display();
    }
}