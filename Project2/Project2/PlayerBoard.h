#pragma once
#include "Board.h"

class PlayerBoard : public Board {

public:
	PlayerBoard() : Board() {}
	~PlayerBoard();
	bool playerLoadBoard(const char** playerBoard, CommonPlayer* player, int rows, int cols);

};