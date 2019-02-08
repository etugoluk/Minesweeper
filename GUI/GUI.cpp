#include "GUI.hpp"

GUI::GUI(int mapSize)
{
    cellSize = screenSize / mapSize;
    windowSize = cellSize * mapSize;
	window.create(sf::VideoMode(windowSize, windowSize + 50), "Minesweeper", sf::Style::Close);

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
    if (!font.loadFromFile("font/Courier.dfont"))
        throw BadFont();

    timer.setFont(font);
    timer.setCharacterSize(25);
    timer.setPosition(10, windowSize + 5);

    state.setFont(font);
    state.setCharacterSize(25);
    state.setPosition(200, windowSize + 5);
}

void GUI::drawCell(Cell const & cell, int x, int y)
{
	sf::Texture texture;
    std::string fileName;

	if (cell.getIsMarked())
        fileName = "img/flaged.png";
    else if (gameStatus == -1 && cell.getIsBomb())
        fileName = "img/bomb.png";
	else if (!cell.getIsVisible())
    	fileName = "img/closed.png";
    else
        fileName = "img/num" + std::to_string(cell.getBombsNear()) + ".png";

    if (!texture.loadFromFile(fileName.c_str()))
        throw BadImage();

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

    if (event.type == sf::Event::Closed)
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
            if (!map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsMarked())
            {
                if (map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsBomb())
                    gameStatus = -1;
                else if (!map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsVisible())
                    logic.setVisibleCells(event.mouseButton.y / cellSize, event.mouseButton.x / cellSize);
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Middle && 
            map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getIsVisible())
        {
            if (map[event.mouseButton.y / cellSize][event.mouseButton.x / cellSize].getBombsNear() <=
                logic.countFlags(event.mouseButton.y / cellSize, event.mouseButton.x / cellSize))
            {
                if (!logic.setPossibleCells(event.mouseButton.y / cellSize, event.mouseButton.x / cellSize))
                    gameStatus = -1;
            }
        }
    }
}

void GUI::refresh(Logic & logic)
{
    gameStatus = 0;
    isFirstClick = 1;
    logic.clearMap();
    window.close();
    window.create(sf::VideoMode(windowSize, windowSize + 50), "Minesweeper", sf::Style::Close);
}

int GUI::execute(Logic & logic)
{
    std::clock_t start = std::clock();

	while (window.isOpen())
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

        // draw Game status
        if (logic.check_win())
            gameStatus = 1;

        if (gameStatus == 1)
            state.setString("YOU WIN :D");
        else if (gameStatus == -1)
            state.setString("YOU LOSE ._.");
        else
            state.setString("YOU CAN DO IT!");
        window.draw(state);

        window.display();

        if (gameStatus)
        {
            sf::sleep(sf::milliseconds(3000));
            return 1;
        }
    }
    return 0;
}

const char * GUI::BadImage::what() const throw()
{
    return "Bad file access to image.";
}

const char * GUI::BadFont::what() const throw()
{
    return "Bad file access to font.";
}
