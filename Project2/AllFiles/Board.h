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
	int PlayerANumOfBoats;
	int PlayerBNumOfBoats;


	virtual void addBoatToBoard(Point* point, int size, int player, IBattleshipGameAlgo* owner, IBattleshipGameAlgo* rival);
	virtual void checkAdjacentBoat(Boat* boat, Point* point, int size, int direction, int player, IBattleshipGameAlgo* owner, IBattleshipGameAlgo* rival);
	void mergeBoats(Boat* boat1, Boat* boat2, int direction);


public:
	Board() : matrix(nullptr), hasAdjacentBoats(false), PlayerANumOfBoats(0), PlayerBNumOfBoats(0){}
	virtual ~Board();
	virtual void setPoint(int row, int col);
	virtual void setVars();

	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;



};