#include "PlayerData.h"

PlayerData::~PlayerData() {
	FreeLibrary(std::get<1>(player_dll));
}

int PlayerData::addData(int win, int lose, int pointsFor, int poinsAgainst) {
	std::lock_guard<std::mutex> l(this->m);
	if (gamesPlayed > 0) {
		this->wins.push_back((this->wins.back() + win));
		this->loses.push_back((this->loses.back() + lose));
		this->pointsFor.push_back((this->pointsFor.back() + pointsFor));
		this->pointsAgainst.push_back((this->pointsAgainst.back() + poinsAgainst));
	}
	else {
		this->wins.push_back(win);
		this->loses.push_back(lose);
		this->pointsFor.push_back(pointsFor);
		this->pointsAgainst.push_back(poinsAgainst);
	}
	return gamesPlayed++;
}

std::tuple<int, int, int, int, std::string> PlayerData::gotRoundData(int round) {
	if (round > this->gamesPlayed) {
		return std::make_tuple(-1, -1, -1, -1, "");
	}

	return std::make_tuple(this->wins[round], this->loses[round],
		this->pointsFor[round], this->pointsAgainst[round], std::get<0>(this->player_dll));
}

IBattleshipGameAlgo* PlayerData::getDLLAlgo() {

	return (*std::get<2>(this->player_dll))();
}
