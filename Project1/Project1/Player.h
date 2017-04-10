#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

#include "Board.h"
#include "Boat.h"
#include <vector>

class Player: public IBattleshipGameAlgo {
	Boat boats[5];
	char player_board[10][10];
	int gameScore;
	int totalScore;
	int wins;
	vector<pair<int, int>> attackMoves;
	int attackNumber;
	int maxMoves;

public:
	Player() : gameScore(0), totalScore(0), wins(0){}
	~Player() {
		delete[] boats;
	}
	virtual void setBoard(const char** board, int numRows, int numCols) override; // called once to notify player on his board
	virtual std::pair<int, int> attack() override; // ask player for his move
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; // notify on last move result
	void getMoves(const string& attackFile);
	void processLine(const string& line);
	static std::vector<std::string> split(const std::string &s, char delim);
	bool hasFinishedAttacking();
	bool hasNoMoreBoats();

};

#endif