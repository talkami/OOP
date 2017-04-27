
#include "SmartPlayer.h"
#include <iostream>

SmartPlayer::SmartPlayer() : gameScore(0), totalScore(0), wins(0), numOfBoats(0) {
}

SmartPlayer::~SmartPlayer() {
	delete[] & player_board;
}

void SmartPlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	memcpy(this->player_board, board, sizeof(char) * numRows * numCols);
	this->playerNum = player;
}

bool SmartPlayer::init(const std::string & path) {

	//CREATE FUNCTION!!!!!

	return true;
}

std::pair<int, int> SmartPlayer::attack() {
	//CREATE FUNCTION!!!

	return std::pair<int, int>(-1,-1);
}

bool SmartPlayer::hasFinishedAttacking() {

	//FUNCTION MAY NEED CORRECTING
	if (this->attackNumber >= this->maxMoves) {
		return true;
	}
	else {
		return false;
	}
}

void SmartPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {}

bool SmartPlayer::hasNoMoreBoats() {
	if (numOfBoats == 0) {
		return true;
	}
	else {
		return false;
	}
}

void SmartPlayer::addBoat() {
	this->numOfBoats += 1;
}

void SmartPlayer::removeBoat() {
	if (this->numOfBoats == 0) {
		std::cout << "Error: Player has no more boats to remove." << std::endl;
	}
	this->numOfBoats -= 1;
}

int SmartPlayer::getNumOfBoats() {
	return this->numOfBoats;
}

int SmartPlayer::getGameScore() {
	return this->gameScore;
}

void SmartPlayer::addWin() {
	this->wins++;
}

void SmartPlayer::increaseScore(int amount) {
	this->gameScore += amount;
	this->totalScore += amount;
}