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
	Logger logger;
	int numOfThreads = 0;
	FilesListerWithSuffix boardFileLister;
	std::vector<std::shared_ptr<Board>> gameBoards;
	std::vector<std::shared_ptr<PlayerData>> players;
	std::deque<std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>>> games;
	bool play = true;

	void setUpLogger(const std::string& path);
	bool setUpBoards(const std::string& path);
	bool setUpPlayers(const std::string& path);
	void createGameCombinations();
	void logTournamentStatistics();
	void startSingleGame();
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> getNextGame();

public:
	bool initTournament(std::string path, int threads);
	bool playTournament();
};