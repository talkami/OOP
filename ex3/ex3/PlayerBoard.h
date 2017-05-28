#pragma once
#include "IBattleshipGameAlgo.h"

class PlayerBoard : BoardData{
	int _rows = 0;
	int _cols = 0;
	int _depth = 0; 
	 

	void invalidatePoint(Coordinate c);
public:

	PlayerBoard(int rows, int cols, int depth) : _rows(rows), _cols(cols), _depth(depth) {}
	virtual char charAt(Coordinate c) const;

};