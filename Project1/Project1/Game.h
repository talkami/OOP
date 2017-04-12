#pragma once

#include "Player.h"
#include "Board.h"
#include "SeaBattleBoardLister.h"
#include "AttackAFileLister.h"
#include "AttackBFileLister.h"


class Game {
	Player A;
	Player B;
	Board gameBoard;
	int turn; //0 for player A, 1 for player B, -1 for victory, -2 if game ended without a victory
	SeaBattleBoardLister boardFileLister;
	AttackAFileLister playerAFileLister;
	AttackBFileLister playerBFileLister;
	char winner;

	bool getInitFiles(const std::string& path);
	bool setNextTurn(AttackResult res);

public:
	Game();
	~Game();
	bool initGame(const std::string& path);
	bool playGame();
	bool endGame();

};
