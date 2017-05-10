#pragma once

#include "NaivePlayer.h"
#include "GameBoard.h"


class Game {
	NaivePlayer A;
	NaivePlayer B;
	GameBoard gameBoard;
	int turn; //0 for player A, 1 for player B, -1 for victory, -2 if game ended without a victory
	char winner;

	bool setNextTurn(AttackResult res, bool selfHit);

public:
	Game() {}
	~Game() {}
	bool initGame(const std::string& path);
	bool playGame();
	bool endGame();

	Game(const Game&) {}
	Game& operator=(const Game&) {}
};
