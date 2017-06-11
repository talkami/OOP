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
#include <thread>
#include <atomic>

class TournamentManager {
	Logger logger;
	size_t nameBuffer = 0;
	int numOfThreads;
	int roundCounter = 0;
	int runningThreads = 0;
	FilesListerWithSuffix boardFileLister;
	std::vector<std::shared_ptr<Board>> gameBoards;
	std::vector<std::shared_ptr<PlayerData>> players;
	std::deque<std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>>> games;
	std::vector<std::thread> threads_vec;
	std::vector<int> playedRounds;
	std::mutex m;
	std::condition_variable cv;

	void setUpLogger(const std::string& path);
	bool setUpBoards(const std::string& path);
	bool setUpPlayers(const std::string& path);
	void createGameCombinations();
	void logTournamentStatistics();
	void startSingleGame();
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> getNextGame();
	void increaseRoundCount(int roundA, int roundB);
	void intermediateResults(int round);

public:
	TournamentManager(int threads) :numOfThreads(threads), threads_vec(threads) {}
	~TournamentManager() {}
	bool initTournament(std::string path);
	bool playTournament();
};