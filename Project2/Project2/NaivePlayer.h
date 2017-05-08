#pragma once
#include "CommonPlayer.h"
#include "PlayerBoard.h"
#include <vector>
#include <utility> 

class NaivePlayer : public CommonPlayer{
	PlayerBoard player_board;
	int attackRow;
	int attackCol;
	bool finishedAttacking;

public:
	NaivePlayer();
	~NaivePlayer();
	virtual void setBoard(int player, const char** board, int numRows, int numCols) override;
	virtual bool init(const std::string& path) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
	virtual bool hasFinishedAttacking() override;

	NaivePlayer(const NaivePlayer&) = delete;
	NaivePlayer& operator=(const NaivePlayer&) = delete;

};

