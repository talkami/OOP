#pragma once
#include "IBattleshipGameAlgo.h"

class SingleGame {
	IBattleshipGameAlgo* PlayerA;
	IBattleshipGameAlgo* PlayerB;
	int scoreA;
	int scoreB;

public:
	SingleGame();

};