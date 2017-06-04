#pragma once
#include <vector>

struct PlayerData {
	int playerID;
	int gamesPlayed;
	std::vector<int> wins;
	std::vector<int> pointsFor;
	std::vector<int> pointsAgainst;

	PlayerData(int id) : playerID(id), gamesPlayed(0){}
	void addData(int gameResult, int playerPoints, int rivalPoins) {

	}
};