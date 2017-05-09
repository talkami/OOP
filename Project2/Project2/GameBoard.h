#pragma once

#include "Boat.h"
#include "Point.h"
#include "SeaBattleBoardLister.h"
#include <utility> // for std::pair

class GameBoard {
	Point* **matrix;
	bool errorArray[9] = { false };
	char** playerABoard;
	char** playerBBoard;
	int numOfRows;
	int numOfCols;

	void addBoatToBoard(Point* point, int i, int j, int size, int player, CommonPlayer* owner, CommonPlayer* rival);
	void addToPlayerBoard(char currentChar, int row, int col, CommonPlayer* A, CommonPlayer* B);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B);
	void checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival);
public:
	GameBoard() : matrix(nullptr), playerABoard(nullptr), playerBBoard(nullptr) {}
	~GameBoard();
	bool initBoard(const std::string& path, CommonPlayer* A, CommonPlayer* B, int rows, int cols);
	bool loadBoard(const std::string& boardFile, CommonPlayer* A, CommonPlayer* B);
	bool updateBoardAfterAttack(Point * point, AttackResult result);
	
	void createBoard(char currentChar, CommonPlayer* A, CommonPlayer* B, int row, int col);
	void setVars();

	bool playerLoadBoard(const char** playerBoard, CommonPlayer* player, int rows, int cols); //brb

	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();
	void setInvalidAttack(int row, int col);
	bool isValidAttack(int row, int col);

	GameBoard(const GameBoard&) = delete;
	GameBoard& operator=(const GameBoard&) = delete;

};