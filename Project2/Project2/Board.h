#pragma once

#include "Boat.h"
#include "Point.h"
#include <utility> // for std::pair

class Board {
	Point* matrix[10][10];
	bool errorArray[9] = { false };
	char** playerABoard;
	char** playerBBoard;
	int rows; // i / x
	int cols; // j / y

	void addBoatToBoard(Point* point, int i, int j, int size, int player, Player* owner, Player* rival);
	void addToPlayerBoard(char currentChar, int row, int col, Player* A, Player* B);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(Player* A, Player* B);
public:
	bool updateBoardAfterAttack (Point * point, AttackResult result);
	bool loadBoard(const std::string& boardFile, Player* A, Player* B, int rows, int cols);
	bool createBoard (char** board, Player* A, Player* B, int rows, int cols);
	void setVars ( int rows, int cols); 
	Board();
 	bool playerLoadBoard (char** playerBoard, Player* player, int rows, int cols); //brb
	~Board();
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();
	void setInvalidAttack(int row, int col);
	bool isValidAttack(int row, int col);

	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

};