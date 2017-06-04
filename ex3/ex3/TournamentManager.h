#pragma once
#include "IBattleshipGameAlgo.h"
#include "GameBoard.h"
#include "FilesListerWithSuffix.h"
#include "PlayerData.h"
#include "Logger.h"

#include <vector>
#include <map> 


class TournamentManager {
	// define function of the type we expect
	typedef IBattleshipGameAlgo *(*GetAlgorithmFuncType)();
	GetAlgorithmFuncType getAlgorithmFunc;
	Logger logger;
	int numOfThreads = 0;
	FilesListerWithSuffix boardFileLister;
	std::vector<GameBoard*> gameBoards;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>> players_vec;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>>::iterator vitr;
	std::vector<PlayerData> players;
	std::vector<std::tuple<PlayerData*, PlayerData*, GameBoard*>> games;

	bool getBoards(const std::string& path);
	bool getDLLs(const std::string& path);
	void setUpLogger(std::string& path);
	void createPlayerData();
	void createGameCombinations();

public:
	bool initGame(std::string path, int threads);
	bool playGame();
};