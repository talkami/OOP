#pragma once

#include "Board.h"
#include "SeaBattleBoardLister.h"
#include <windows.h>

class GameBoard : public Board {
	bool errorArray[8] = { false };
	char** playerABoard;
	char** playerBBoard;
	bool display;
	int colors[2] = { 207,159 };
	int PlayerAScore;
	int PlayerBScore;



	void addToPlayerBoard(char currentChar, int row, int col, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B);
	void checkBoatValidity();
	bool checkBoard();
	bool checkNumOfPlayersBoats(IBattleshipGameAlgo* A, IBattleshipGameAlgo* B);

public:
	GameBoard() : Board(), playerABoard(nullptr), playerBBoard(nullptr) {}
	~GameBoard();

	bool initBoard(const std::string& path, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B, int rows, int cols, bool display);
	bool loadBoard(const std::string& boardFile, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B);

	virtual void setVars() override;
	AttackResult play_attack(std::pair <int, int> attack, int attacker, bool* selfHit);
	char** getPlayerABoard();
	char** getPlayerBBoard();

	GameBoard(const GameBoard&) = delete;
	GameBoard& operator=(const GameBoard&) = delete;

	static void gotoxy(int x, int y);
	static void setTextColor(int color);
	static void GameBoard::hideCursor();
	static void addToDisplay(int x, int y, int color, char c);
	void displayBoard();
	void displayAttack(AttackResult result, int x, int y, int delay);
	void GameBoard::sinkBoatAnimation(Boat* boat, int color, int delay);

	//new func
	bool hasNoMoreBoats(int player);
	void removeBoat(int player);
	int getNumOfBoats(int player);
	int getGameScore(int player);
	void increaseScore(int amount, int player);

};