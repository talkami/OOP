
#include "NaivePlayer.h"
#include <iostream>

NaivePlayer::NaivePlayer() : 
	gameScore(0), 
	totalScore(0), 
	wins(0), 
	numOfBoats(0), 
	attackRow(0), 
	attackCol(0), 
	finishedAttacking(false){}

NaivePlayer::~NaivePlayer() {
	delete[] & player_board;
}

void NaivePlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	memcpy(this->player_board, board, sizeof(char) * numRows * numCols);
	this->playerNum = player;
	this->rowNum = numRows;
	this->colNum = numCols;
}

bool NaivePlayer::init(const std::string & path) {

	//CREATE FUNCTION!!!!!

	return true;
}

std::pair<int, int> NaivePlayer::attack() {
	//CREATE FUNCTION!!!
	//i think we should invalidate squares in the player_board and then do the following loop:

	while (player_board[this->attackRow][this->attackCol] != ' ') {
		if (this->attackCol < colNum-1) {
			this->attackCol++;
		}
		else {
			if (this->attackRow < rowNum-1) {
				this->attackCol = 0;
				this->attackRow++;
			}
			else {
				this->finishedAttacking = true;
				return std::pair<int, int>(-1, -1);
			}
		}
	}

	std::pair<int, int> res(this->attackRow, this->attackCol);

	if (this->attackCol < colNum - 1) {
		this->attackCol++;
	}
	else {
		if (this->attackRow < rowNum - 1) {
			this->attackCol = 0;
			this->attackRow++;
		}
		else {
			this->finishedAttacking = true;
		}
	}
	return res;
}

void NaivePlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	//here we invalidate squares in the player_board
}

bool NaivePlayer::hasFinishedAttacking() {
	return this->finishedAttacking;
}

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