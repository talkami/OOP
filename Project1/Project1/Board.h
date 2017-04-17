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
	bool errorArray[9] = { false };
	char** playerABoard;
	char** playerBBoard;

	void addBoatToBoard(Point* point, int i, int j, int size, int player, Player* owner, Player* rival);
	void addToPlayerBoard(char currentChar, int row, int col, Player* A, Player* B);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(Player* A, Player* B);
public:

	bool loadBoard(const std::string& boardFile, Player* A, Player* B);
	Board();
	~Board();
	AttackResult play_attack(std::pair <int, int> attack);
	char** getPlayerABoard();
	char** getPlayerBBoard();

	//unused constructor
	//Board(const string& boardFile);

};