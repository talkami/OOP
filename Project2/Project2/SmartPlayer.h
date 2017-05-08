#pragma once
#include "CommonPlayer.h"
#include "Board.h"
#include "Point.h"
#include <vector>
#include <utility> 

class SmartPlayer : public CommonPlayer {
	Board player_board;
	int attackRow;
	int attackCol;
	bool finishedAttacking;

	//add spaciel fields
	bool isThereGoodAttack;
	int horizonalGoodAttack; //0 dont know, 1 horizontal, 2 the other direction...
	Point* down;
	Point* up;
	Point* left;
	Point* right;



public:
	SmartPlayer();
	~SmartPlayer();
	virtual void setBoard(int player, const char** board, int numRows, int numCols) override;
	virtual bool init(const std::string& path) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
	virtual bool hasFinishedAttacking() override;

	SmartPlayer(const SmartPlayer&) = delete;
	SmartPlayer& operator=(const SmartPlayer&) = delete;

};
