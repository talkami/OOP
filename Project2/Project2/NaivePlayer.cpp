
#include "NaivePlayer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

NaivePlayer::NaivePlayer() : gameScore(0), totalScore(0), wins(0), numOfBoats(0) {
}
NaivePlayer::~NaivePlayer() {
	delete[] & player_board;
}

void NaivePlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	memcpy(this->player_board, board, sizeof(char) * numRows * numCols);
	this->playerNum = player;
}

bool NaivePlayer::init(const std::string & path) {

	//CREATE FUNCTION!!!!!

	return true;
}

std::pair<int, int> NaivePlayer::attack() {
	//CREATE FUNCTION!!!

	return std::pair<int, int>(-1, -1);

}

bool NaivePlayer::hasFinishedAttacking() {

	//FUNCTION MAY NEED CORRECTING
	if (this->attackNumber >= this->maxMoves) {
		return true;
	}
	else {
		return false;
	}
}

void NaivePlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {}

bool NaivePlayer::hasNoMoreBoats() {
	if (numOfBoats == 0) {
		return true;
	}
	else {
		return false;
	}
}

void NaivePlayer::addBoat() {
	this->numOfBoats += 1;
}

void NaivePlayer::removeBoat() {
	if (this->numOfBoats == 0) {
		std::cout << "Error: Player has no more boats to remove." << std::endl;
	}
	this->numOfBoats -= 1;
}

int NaivePlayer::getNumOfBoats() {
	return this->numOfBoats;
}

int NaivePlayer::getGameScore() {
	return this->gameScore;
}

void NaivePlayer::addWin() {
	this->wins++;
}

void NaivePlayer::increaseScore(int amount) {
	this->gameScore += amount;
	this->totalScore += amount;
}