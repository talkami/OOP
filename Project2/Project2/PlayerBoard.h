#pragma once

#include "Board.h"

class PlayerBoard : public Board{

	void setBoard(const char** board, int player, CommonPlayer* owner);
	void setInvalidArea(Point* point);

public:
	PlayerBoard() : Board() {}
	~PlayerBoard() {}

	bool loadBoard(const char** board, int player, CommonPlayer* owner, int rows, int cols);

	void setInvalidAttack(int row, int col);
	bool isValidAttack(int row, int col);
	bool updateBoardAfterAttack(int row, int col, AttackResult result);

	PlayerBoard(const PlayerBoard&) = delete;
	PlayerBoard& operator=(const PlayerBoard&) = delete;

};