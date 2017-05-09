#pragma once

#include "Boat.h"
#include "Point.h"
#include <utility>

class Board {
protected:
	Point* **matrix;
	int numOfRows;
	int numOfCols;

public:
	Board() : matrix(nullptr) {}
	virtual ~Board();
	virtual void setPoint(int row, int col);
	virtual void setVars();
	
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;


/*
//still need to check
	
	bool errorArray[9] = { false };

	void addBoatToBoard(Point* point, int i, int j, int size, int player, CommonPlayer* owner, CommonPlayer* rival);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B);
	void checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival);

	bool updateBoardAfterAttack(Point * point, AttackResult result);
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	void setInvalidAttack(int row, int col);
	bool isValidAttack(int row, int col);
*/
};