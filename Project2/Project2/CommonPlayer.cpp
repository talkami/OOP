#include "CommonPlayer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

CommonPlayer::CommonPlayer() : gameScore(0), totalScore(0), wins(0), numOfBoats(0) {
}
CommonPlayer::~CommonPlayer() {}

bool CommonPlayer::hasFinishedAttacking() {
	if (this->attackNumber >= this->maxMoves) {
		return true;
	}
	else {
		return false;
	}
}

bool CommonPlayer::hasNoMoreBoats(){
	if (numOfBoats == 0) {
		return true;
	}
	else {
		return false;
	}
}

void CommonPlayer::addBoat() {
	this->numOfBoats += 1;
}

void CommonPlayer::removeBoat() {
	if (this->numOfBoats == 0) {
		std::cout << "Error: CommonPlayer has no more boats to remove." << std::endl;
	}
	this->numOfBoats -= 1;
}

int CommonPlayer::getNumOfBoats() {
	return this->numOfBoats;
}

int CommonPlayer::getGameScore() {
	return this->gameScore;
}

void CommonPlayer::addWin() {
	this->wins++;
}

void CommonPlayer::increaseScore(int amount) {
	this->gameScore += amount;
	this->totalScore += amount;
}