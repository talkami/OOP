#pragma once


#include "Boat.h"
#include "Point.h"
#include <string>
#include <utility> // for std::pair

class Board {
	Point* matrix[10][10];
	//(0) Wrong size or shape for ship <char> for player A,	(1) Wrong size or shape for ship <char> for player B
	//(2) Too many ships for player A, (3) Too few ships for player A
	//(4) Too many ships for player B, (5) Too few ships for player B, (6) Adjacent Ships on Board
	bool errorArray[7] = { false };
	mutable char** playerABoard;
	mutable char** playerBBoard;

	void setBoardsToPoint(Point* point, int i, int j, int size, int player, Player* A, Player* B);
public:

	void loadBoard(const std::string& boardFile, Player* A, Player* B);
	Board();
	~Board();
	AttackResult play_attack(std::pair <int, int> attack);
	char** getPlayerABoard();
	char** getPlayerBBoard();

	//unused constructor
	//Board(const string& boardFile);

};