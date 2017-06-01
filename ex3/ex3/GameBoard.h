#pragma once
#include "IBattleshipGameAlgo.h"

class GameBoard : BoardData {

public:

	GameBoard() {}
	virtual char charAt(Coordinate c) const;

};