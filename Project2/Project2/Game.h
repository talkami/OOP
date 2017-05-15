#pragma once

#include "CommonPlayer.h"
#include "GameBoard.h"


class Game {
	bool displayGame;
	int delay;
	CommonPlayer* A;
	CommonPlayer* B;
	GameBoard gameBoard;
	int turn; //0 for player A, 1 for player B, -1 for victory, -2 if game ended without a victory
	char winner;
	std::string path;

	bool setNextTurn(AttackResult res, bool selfHit);
	bool setupGame(const std::string& path);

public:
	Game() : displayGame(true) , delay(900){}
	~Game();
	bool initGame(int argc, char* argv[], CommonPlayer* playerA, CommonPlayer* playerB);
	bool playGame();
	bool endGame();

	Game(const Game&) {}
	Game& operator=(const Game&) {}
};
