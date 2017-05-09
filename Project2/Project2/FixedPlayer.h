#pragma once
#include "CommonPlayer.h"
#include "AttackAFileLister.h"
#include "AttackBFileLister.h"
#include <vector>
#include <utility> 

class FixedPlayer: public CommonPlayer {
	char player_board;
	std::vector<std::pair<int, int>> attackMoves;
	int attackNumber;
	size_t maxMoves;

	void processLine(const std::string& line);
	static std::vector<std::string> split(const std::string &s, char delim);

public:
	FixedPlayer(){}
	~FixedPlayer(){}
	virtual void setBoard(int player, const char** board, int numRows, int numCols) override;
	virtual bool init(const std::string& path) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; 
	virtual bool hasFinishedAttacking() override;
	void getMoves(const std::string& attackFile);

	FixedPlayer(const FixedPlayer&) {}
	FixedPlayer& operator=(const FixedPlayer&) {}

};
