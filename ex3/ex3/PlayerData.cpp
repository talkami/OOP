#include "PlayerData.h"

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

	return std::make_tuple(this->wins[round], this->pointsFor[round], this->pointsAgainst[round]);
}
