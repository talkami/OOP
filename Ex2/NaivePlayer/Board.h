#pragma once

#include "Point.h"
#include <string>
#include <fstream>
#include <iostream>
#include <utility>


class Board {
protected:
	Point* **matrix;
	int numOfRows;
	int numOfCols;
	bool hasAdjacentBoats;

	virtual void addBoatToBoard(Point* point, int size, int player, CommonPlayer* owner, CommonPlayer* rival);
	virtual void checkAdjacentBoat(Boat* boat, Point* point, int size, int direction, int player, CommonPlayer* owner, CommonPlayer* rival);
	void mergeBoats(Boat* boat1, Boat* boat2, int direction);


public:
	Board() : matrix(nullptr), hasAdjacentBoats(false) {}
	virtual ~Board();
	virtual void setPoint(int row, int col);
	virtual void setVars();

	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

};