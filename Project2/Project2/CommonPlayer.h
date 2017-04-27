#pragma once
#include "IBattleshipGameAlgo.h"

#include <vector>
#include <utility> 

class CommonPlayer {

public:
	CommonPlayer() : gameScore(0), totalScore(0), wins(0), numOfBoats(0) {}
	virtual ~CommonPlayer() {};
	virtual bool hasFinishedAttacking() = 0;
	bool hasNoMoreBoats();
	void addBoat();
	void removeBoat();
	int getNumOfBoats();
	int getGameScore();
	void addWin();
	void increaseScore(int amount);

	CommonPlayer(const CommonPlayer&) = delete;
	CommonPlayer& operator=(const CommonPlayer&) = delete;

protected:
	int gameScore;
	int totalScore;
	int wins;
	int maxMoves;
	int numOfBoats;	
	int numOfRows = 0;
	int numOfCols = 0;
	int playerNum = -1;


};
