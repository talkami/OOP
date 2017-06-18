#pragma once
#include "Logger.h"
#include "FilesListerWithSuffix.h"
#include "Board.h"
#include "PlayerData.h"
#include "IBattleshipGameAlgo.h"

#include <vector>
#include <deque>
#include <atomic>

class TournamentManager {
	size_t nameBuffer = 0;
	int roundCounter = 0;
	std::atomic_int runningThreads = 0;
	int numOfThreads;
	Logger logger;
	FilesListerWithSuffix boardFileLister;
	std::vector<std::shared_ptr<Board>> gameBoards;
	std::vector<std::shared_ptr<PlayerData>> players;
	std::deque<std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>>> games;
	std::vector<std::thread> threads_vec;
	std::vector<int> playedRounds;
	std::mutex resultsMutex;
	std::condition_variable cv;

	void setUpLogger(const std::string& path);
	bool setUpBoards(const std::string& path);
	bool setUpPlayers(const std::string& path);
	void createGameCombinations();
	void logTournamentStatistics();
	void threadRunner();
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> getNextGame();
	void increaseRoundCount(int roundA, int roundB);
	bool intermediateResults(int round);

public:
	TournamentManager(int threads) :numOfThreads(threads), threads_vec(threads) {}
	~TournamentManager() {}
	bool initTournament(std::string path);
	bool playTournament();
};