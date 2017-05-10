#pragma once

#include "Boat.h"
#include "Point.h"
#include <utility>
#include <string>
#include <fstream>
#include <iostream>

class Board {
protected:
	Point* **matrix;
	int numOfRows;
	int numOfCols;
	bool adjacentBoats;

	virtual void addBoatToBoard(Point* point, int size, int player, CommonPlayer* owner, CommonPlayer* rival);
	virtual void checkAdjacentBoat(Boat* boat, Point* point, int size, int direction, int player, CommonPlayer* owner, CommonPlayer* rival);


public:
	Board() : matrix(nullptr), adjacentBoats(false) {}
	virtual ~Board();
	virtual void setPoint(int row, int col);
	virtual void setVars();
	
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

};