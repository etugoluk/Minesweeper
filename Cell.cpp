#include "Cell.hpp"

Cell::Cell() : isVisible(false), isBomb(false), isMarked(false), bombsNear(0)
{}

Cell::~Cell()
{}

bool Cell::getIsVisible() const { return isVisible; }

bool Cell::getIsBomb() const { return isBomb; }

bool Cell::getIsMarked() const { return isMarked; } 

int  Cell::getBombsNear() const { return bombsNear; }

void Cell::setIsMarked(bool b) { isMarked = b; }

void Cell::setIsVisible(bool b) { isVisible = b; }

void Cell::setIsBomb(bool b) { isBomb = b; }

void Cell::setBombsNear(int i) { bombsNear = i; }