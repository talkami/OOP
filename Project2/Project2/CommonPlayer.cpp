#include "CommonPlayer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

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
		std::cout << "Error: player ";
		this->playerNum == 1 ? std::cout << "A" : std::cout << "B";
		std::cout << " has no more boats to remove." << std::endl;
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