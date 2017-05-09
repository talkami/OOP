#pragma once

#include "Board.h"
#include "SeaBattleBoardLister.h"

class GameBoard : public Board{
	bool errorArray[9] = { false };
	char** playerABoard;
	char** playerBBoard;

	void addBoatToBoard(Point* point, int size, int player, CommonPlayer* owner, CommonPlayer* rival);
	void addToPlayerBoard(char currentChar, int row, int col, CommonPlayer* A, CommonPlayer* B);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B);
	void checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival);

public:
	GameBoard() : Board(), playerABoard(nullptr), playerBBoard(nullptr) {}
	~GameBoard();

	bool initBoard(const std::string& path, CommonPlayer* A, CommonPlayer* B, int rows, int cols);
	bool loadBoard(const std::string& boardFile, CommonPlayer* A, CommonPlayer* B);
	
	virtual void setVars() override;
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();

	GameBoard(const GameBoard&) = delete;
	GameBoard& operator=(const GameBoard&) = delete;

};