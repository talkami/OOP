#pragma once
#include "Board.h"

class GameBoard : public Board{
	char** playerABoard;
	char** playerBBoard;


public:
	GameBoard() : Board(), playerABoard(nullptr), playerBBoard(nullptr) {}
	~GameBoard();
	char** getPlayerABoard();
	char** getPlayerBBoard();

};