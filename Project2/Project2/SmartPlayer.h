#pragma once
#include "IBattleshipGameAlgo.h"
#include <vector>
#include <utility> 

class SmartPlayer : public IBattleshipGameAlgo {
	char player_board[10][10];
	int gameScore;
	int totalScore;
	int wins;
	std::vector<std::pair<int, int>> attackMoves;
	int attackNumber;
	size_t maxMoves;
	int numOfBoats;
	int playerNum;

	//add spaciel fields
	bool isThereGoodAttack;
	int horizonalGoodAttack; //0 dont know, 1 horizontal, 2 the other direction...
	point* down;
	point* up;
	point* left;
	point* right;



public:
	SmartPlayer();
	~SmartPlayer();
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

	SmartPlayer(const SmartPlayer&) {}
	SmartPlayer& operator=(const SmartPlayer&) {}

};
