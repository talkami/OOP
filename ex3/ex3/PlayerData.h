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
	std::vector<int> loses;
	std::vector<int> pointsFor;
	std::vector<int> pointsAgainst;
	std::mutex m;
public:
	PlayerData(int id, std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType> dll) :
		gamesPlayed(0), player_dll(dll){}
	~PlayerData();
	int addData(int win, int lose, int pointsFor, int poinsAgainst);
	//gotRoundData returns: num of wins, pts for, num of loses, pts against, dll name
	std::tuple<int, int, int, int, std::string> gotRoundData(int round);
	std::unique_ptr<IBattleshipGameAlgo> getDLLAlgo();

};