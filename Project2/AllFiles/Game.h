#pragma once

#include "IBattleshipGameAlgo.h"
#include "GameBoard.h"
#include <iostream> 
#include <map> 
#include <vector>
#include <string> 
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>


class Game {
	typedef IBattleshipGameAlgo *(*GetAlgorithmFuncType)();
	GetAlgorithmFuncType getAlgorithmFunc;

	bool displayGame;
	bool AFinishedAttacking;
	bool BFinishedAttacking;
	int delay;
	IBattleshipGameAlgo* A;
	IBattleshipGameAlgo* B;
	GameBoard gameBoard;
	int turn; //0 for player A, 1 for player B, -1 for victory, -2 if game ended without a victory
	char winner;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>> dll_vec;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>>::iterator vitr;

	bool setNextTurn(AttackResult res, bool selfHit);
	bool setupGame(const std::string& path);
	bool setupPlayers(const std::string& path);

public:
	Game() : AFinishedAttacking(false), BFinishedAttacking(false), turn(0), displayGame(true), delay(900) {}
	~Game();
	bool initGame(int argc, char* argv[]);
	bool playGame();
	bool endGame();

	Game(const Game&) {}
	Game& operator=(const Game&) {}
};
