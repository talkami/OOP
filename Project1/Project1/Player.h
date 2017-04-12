#pragma once
#include "IBattleshipGameAlgo.h"

#include <vector>
#include <utility> 

class Player: public IBattleshipGameAlgo {
	char player_board[10][10];
	int gameScore;
	int totalScore;
	int wins;
	std::vector<std::pair<int, int>> attackMoves;
	int attackNumber;
	int maxMoves;
	int numOfBoats;

public:
	Player();
	~Player();
	virtual void setBoard(const char** board, int numRows, int numCols) override; // called once to notify player on his board
	virtual std::pair<int, int> attack() override; // ask player for his move
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result
	void getMoves(const std::string& attackFile);
	void processLine(const std::string& line);
	static std::vector<std::string> split(const std::string &s, char delim);
	bool hasFinishedAttacking();
	bool hasNoMoreBoats();
	void addBoat();
	void removeBoat();
	int getNumOfBoats();
	int getGameScore();
	void addWin();
	void increaseScore(int amount);
};
