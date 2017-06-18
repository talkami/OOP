#pragma once
#include "IBattleshipGameAlgo.h"
#include "Board.h"
#include "PlayerData.h"

class SingleGame {
	std::shared_ptr<PlayerData> dataA;
	std::shared_ptr<PlayerData> dataB;
	std::unique_ptr<IBattleshipGameAlgo> PlayerA;
	std::unique_ptr<IBattleshipGameAlgo> PlayerB;
	std::unique_ptr<GameBoard> board;
	int turn;
	int winner;
	bool AFinishedAttacking;
	bool BFinishedAttacking;

	void setNextTurn(AttackResult res, bool selfHit);

public:
	SingleGame(std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> gameStats);
	~SingleGame() {}
	std::pair<int, int> playSingleGame();
};