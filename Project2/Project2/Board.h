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
	void checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival);
public:
	Board(): matrix(nullptr), playerABoard(nullptr), playerBBoard(nullptr){}
	~Board();
	bool updateBoardAfterAttack (Point * point, AttackResult result);
	bool loadBoard(const std::string& boardFile, CommonPlayer* A, CommonPlayer* B, int rows, int cols);
	void createBoard (char currentChar, CommonPlayer* A, CommonPlayer* B, int row, int col);
	void setVars(bool isPlayerBoard);
	
 	bool playerLoadBoard (char** playerBoard, CommonPlayer* player, int rows, int cols); //brb
	
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();
	void setInvalidAttack(int row, int col);
	bool isValidAttack(int row, int col);
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

};