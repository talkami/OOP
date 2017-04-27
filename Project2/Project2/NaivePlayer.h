#pragma once
#include "IBattleshipGameAlgo.h"
#include <vector>
#include <utility> 

class NaivePlayer : public IBattleshipGameAlgo {
	char player_board[10][10];
	int gameScore;
	int totalScore;
	int wins;
	int numOfBoats;
	int playerNum;
	int attackRow;
	int attackCol;
	bool finishedAttacking;
	int colNum;
	int rowNum;

public:
	NaivePlayer();
	~NaivePlayer();
	virtual void setBoard(int player, const char** board, int numRows, int numCols) override;
	virtual bool init(const std::string& path) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
	bool hasFinishedAttacking();
	bool hasNoMoreBoats();
	void addBoat();
	void removeBoat();
	int getNumOfBoats();
	int getGameScore();
	void addWin();
	void increaseScore(int amount);

	NaivePlayer(const NaivePlayer&) {}
	NaivePlayer& operator=(const NaivePlayer&) {}

};
