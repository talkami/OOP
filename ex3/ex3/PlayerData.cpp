#include "PlayerData.h"

PlayerData::~PlayerData() {
	FreeLibrary(std::get<1>(player_dll));
}

void PlayerData::addData(int gameResult, int playerPoints, int rivalPoins) {
	std::lock_guard<std::mutex> l(this->m);
	if (gamesPlayed > 0) {
		wins.push_back((wins.back() + gameResult));
		pointsFor.push_back((pointsFor.back() + playerPoints));
		pointsAgainst.push_back((pointsAgainst.back() + rivalPoins));
	}
	else {
		wins.push_back(gameResult);
		pointsFor.push_back(playerPoints);
		pointsAgainst.push_back(rivalPoins);
	}
	gamesPlayed += 1;
}

std::tuple<int, int, int> PlayerData::gotRoundData(int round) {
	if (round > this->gamesPlayed) {
		return std::make_tuple(-1, -1, -1);
	}

	return std::make_tuple(this->wins[round-1], this->pointsFor[round-1], this->pointsAgainst[round-1]);
}

IBattleshipGameAlgo* PlayerData::getDLLAlgo() {

	return (*std::get<2>(this->player_dll))();
}
