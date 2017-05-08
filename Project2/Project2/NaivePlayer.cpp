#include "NaivePlayer.h"
#include <iostream>

NaivePlayer::NaivePlayer() : 
	CommonPlayer(), 
	attackRow(0), 
	attackCol(0), 
	finishedAttacking(false) {}

NaivePlayer::~NaivePlayer() {}

void NaivePlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	this->playerNum = player;
	this->numOfRows = numRows;
	this->numOfCols = numCols;
	this->player_board.playerLoadBoard(board, this, numRows, numCols);
}

bool NaivePlayer::init(const std::string & path) {

	//CREATE FUNCTION!!!!!

	return true;
}

std::pair<int, int> NaivePlayer::attack() {

	while (this->attackRow < this->numOfRows) {
		while (this->attackCol < this->numOfCols) {
			if (player_board.isValidAttack(this->attackRow, this->attackCol)) {
				return std::pair<int, int>(this->attackRow + 1, ++this->attackCol);
			}
			attackCol++;
		}
		this->attackRow++;
		this->attackCol = 0;
	}
	this->finishedAttacking = true;
	return std::pair<int, int>(-1, -1);
}


void NaivePlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	//COMPLETE FUNCTION

}

bool NaivePlayer::hasFinishedAttacking() {
	return this->finishedAttacking;
}


