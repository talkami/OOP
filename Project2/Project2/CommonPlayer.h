#pragma once
#include "IBattleshipGameAlgo.h"

#include <vector>
#include <utility> 

class CommonPlayer {
	int gameScore;
	int totalScore;
	int wins;
	int attackNumber;
	int maxMoves;
	int numOfBoats;

public:
	CommonPlayer();
	~CommonPlayer();
	bool hasFinishedAttacking();
	bool hasNoMoreBoats();
	void addBoat();
	void removeBoat();
	int getNumOfBoats();
	int getGameScore();
	void addWin();
	void increaseScore(int amount);

	CommonPlayer(const CommonPlayer&) = delete;
	CommonPlayer& operator=(const CommonPlayer&) = delete;

};
