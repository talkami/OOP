#pragma once

#include "IBattleshipGameAlgo.h
#include "GameBoard.h"


class Game {
	bool displayGame;
	int delay;
	IBattleshipGameAlgo* A;
	IBattleshipGameAlgo* B;
	GameBoard gameBoard;
	int turn; //0 for player A, 1 for player B, -1 for victory, -2 if game ended without a victory
	char winner;
	std::string path;

	bool setNextTurn(AttackResult res, bool selfHit);
	bool setupGame(const std::string& path);
	bool setupPlayers(const std::string& path);
	// added fields
	bool HasPlayerAFinishedAttacking;
	bool HasPlayerBFinishedAttacking;
	bool DoesPlayerAOutOfBoats;
	bool DoesPlayerBOutOfBoats;


public:
	Game() : displayGame(true), delay(900) {}
	~Game();
	bool initGame(int argc, char* argv[]);
	bool playGame();
	bool endGame();

	Game(const Game&) {}
	Game& operator=(const Game&) {}
};
