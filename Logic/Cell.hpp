#pragma once

class Cell
{
	bool isVisible;
	bool isBomb;
	bool isMarked;
	int  bombsNear;
public:
	Cell();
	~Cell();

	bool getIsVisible() const;
	bool getIsBomb() const;
	bool getIsMarked() const;
	int  getBombsNear() const;

	void setIsVisible(bool b);
	void setIsBomb(bool b);
	void setIsMarked(bool b);
	void setBombsNear(int i);
};