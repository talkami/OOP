#pragma once
#include "CommonPlayer.h"
#include "PlayerBoard.h"
#include <vector>
#include <utility> 

class SmartPlayer : public CommonPlayer {
	PlayerBoard player_board;
	int attackRow;
	int attackCol;
	bool finishedAttacking;
	bool isThereGoodAttack;
	int horizonalGoodAttack; //0 dont know, 1 horizontal, 2 the other direction...
	int currentAttack; // 1 up 2 down 3 left 4 right, 0 irrelevant
	std::pair<int,int> down;
	std::pair<int,int> up;
	std::pair<int, int>left;
	std::pair<int, int> right;



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

//unique func
	AttackResult getFormerAttackResult ();
	void handleAttackResult (AttackResult result);
	std::pair <int,int> playGoodAttack();

};
