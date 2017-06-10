#pragma once
#include "IBattleshipGameAlgo.h"
#include <vector>
#include <map>
#include <mutex>
#include <windows.h>

typedef IBattleshipGameAlgo *(*GetAlgorithmFuncType)();

class PlayerData {

	int playerID;
	int gamesPlayed;
	std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType> player_dll;
	std::vector<int> wins;
	std::vector<int> pointsFor;
	std::vector<int> pointsAgainst;
	std::mutex m;
public:
	PlayerData(int id, std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType> dll) :
		playerID(id), gamesPlayed(0), player_dll(dll){}
	~PlayerData();
	void addData(int gameResult, int playerPoints, int rivalPoins);
	std::tuple<int, int, int> gotRoundData(int round);
	IBattleshipGameAlgo* getDLLAlgo();

};