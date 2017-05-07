#pragma once

#include "Boat.h"
#include "Point.h"
#include <utility> // for std::pair

class Board {
	Point* **matrix;
	bool errorArray[9] = { false };
	char** playerABoard;
	char** playerBBoard;
	int numOfRows; // i / x
	int numOfCols; // j / y

	void addBoatToBoard(Point* point, int i, int j, int size, int player, CommonPlayer* owner, CommonPlayer* rival);
	void addToPlayerBoard(char currentChar, int row, int col, CommonPlayer* A, CommonPlayer* B);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B);
public:
	Board(){}
	~Board();
	bool updateBoardAfterAttack (Point * point, AttackResult result);
	bool loadBoard(const std::string& boardFile, CommonPlayer* A, CommonPlayer* B, int rows, int cols);
	bool createBoard (char** board, CommonPlayer* A, CommonPlayer* B, int rows, int cols);
	void setVars(); 
	
 	bool playerLoadBoard (char** playerBoard, CommonPlayer* player, int rows, int cols); //brb
	
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();
	void setInvalidAttack(int row, int col);
	bool isValidAttack(int row, int col);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

};