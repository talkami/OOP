#pragma once
#include "Logger.h"
#include "FilesListerWithSuffix.h"
#include "Board.h"
#include "PlayerData.h"
#include "IBattleshipGameAlgo.h"

#include <vector>
#include <map>
#include <memory>
#include <deque>


class TournamentManager {
	// define function of the type we expect
	typedef IBattleshipGameAlgo *(*GetAlgorithmFuncType)();
	GetAlgorithmFuncType getAlgorithmFunc;

	Logger logger;
	int numOfThreads = 0;
	FilesListerWithSuffix boardFileLister;
	std::vector<std::shared_ptr<Board>> gameBoards;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>> players_dll;
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>>::iterator vitr;
	std::vector<std::shared_ptr<PlayerData>> players;
	std::deque<std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>>> games;
	bool play = true;

	void setUpLogger(const std::string& path);
	bool getBoards(const std::string& path);
	bool getDLLs(const std::string& path);
	void createPlayerData();
	void createGameCombinations();
	void logTournamentStatistics();
	void startSingleGame();
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> getNextGame();

public:
	bool initTournament(std::string path, int threads);
	bool playTournament();
};