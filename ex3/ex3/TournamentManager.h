#pragma once
#include "IBattleshipGameAlgo.h"
#include "GameBoard.h"
#include "FilesListerWithSuffix.h"

#include <vector>
#include <map> 


class TournamentManager {
	// define function of the type we expect
	typedef IBattleshipGameAlgo *(*GetAlgorithmFuncType)();
	GetAlgorithmFuncType getAlgorithmFunc;

	int numOfThreads = 0;
	FilesListerWithSuffix boardFileLister;
	std::vector<GameBoard*> gameBoards;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>> dll_vec;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>>::iterator vitr;

	bool getBoards(const std::string& path);
	bool getDLLs(const std::string& path);

public:
	bool initGame(int argc, char* argv[]);
	bool playGame();
};