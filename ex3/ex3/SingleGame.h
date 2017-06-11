#pragma once
#include "IBattleshipGameAlgo.h"
#include "Board.h"
#include "PlayerData.h"

class SingleGame {
	std::shared_ptr<PlayerData> dataA;
	std::shared_ptr<PlayerData> dataB;
	std::shared_ptr<Board> gameBoard;
	IBattleshipGameAlgo* PlayerA;
	IBattleshipGameAlgo* PlayerB;
	int scoreA;
	int scoreB;

	//new vars
	bool AFinishedAttacking;
	bool BFinishedAttacking;
	int turn;

public:
	//optional argument for c'tor - maybe change to something better
	SingleGame(std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> gameStats);
	~SingleGame();
};