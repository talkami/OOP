#pragma once
#include <vector>
#include <map>
#include <mutex>

class PlayerData {
	std::mutex m;
	int playerID;
	int gamesPlayed;
	std::vector<int> wins;
	std::vector<int> pointsFor;
	std::vector<int> pointsAgainst;

public:
	PlayerData(int id) : playerID(id), gamesPlayed(0){}
	void addData(int gameResult, int playerPoints, int rivalPoins);
	std::tuple<int, int, int> gotRoundData(int round);
};