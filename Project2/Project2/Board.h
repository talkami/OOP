#pragma once

#include "Boat.h"
#include "Point.h"
#include <utility> // for std::pair

class Board {
	Point* matrix[10][10];
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
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();

	Board(const Board&) {}
	Board& operator=(const Board&) {}

};