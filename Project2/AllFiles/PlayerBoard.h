#pragma once

#include "Board.h"

class PlayerBoard : public Board {

	void setBoard(const char** board, int player, CommonPlayer* owner);
	void setInvalidArea(Point* point);
	void setInvalidHorizontal(Point* point);
	void setInvalidVertical(Point* point);

	

public:
	PlayerBoard() : Board() {}
	~PlayerBoard() {}

	bool loadBoard(const char** board, int player, CommonPlayer* owner, int rows, int cols);
	bool isValidAttack(int row, int col);
	bool updateBoardAfterAttack(int row, int col, AttackResult result);
	void setInvalidAttack(int row, int col);
	void setInvalidArea(int row, int col);
	void setInvalidHorizontal(int row, int col);
	void setInvalidVertical(int row, int col);

	PlayerBoard(const PlayerBoard&) = delete;
	PlayerBoard& operator=(const PlayerBoard&) = delete;

};