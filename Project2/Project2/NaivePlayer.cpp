#include "NaivePlayer.h"
#include <iostream>

NaivePlayer::NaivePlayer() : 
	CommonPlayer(), 
	attackRow(0), 
	attackCol(0), 
	finishedAttacking(false){}

NaivePlayer::~NaivePlayer() {}

void NaivePlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	this->playerNum = player;
	this->numOfRows = numRows;
	this->numOfCols = numCols;
	//this->player_board = Board();
}

bool NaivePlayer::init(const std::string & path) {

	//CREATE FUNCTION!!!!!

	return true;
}

std::pair<int, int> NaivePlayer::attack() {

	while (!player_board.isValidAttack(this->attackRow, this->attackCol)) {
		if (this->attackCol < numOfCols-1) {
			this->attackCol++;
		}
		else {
			if (this->attackRow < numOfRows - 1) {
				this->attackCol = 0;
				this->attackRow++;
			}
			else {
				this->finishedAttacking = true;
				return std::pair<int, int>(-1, -1);
			}
		}
	}
	player_board.setInvalidAttack(attackRow, attackRow);
	
	return std::pair<int, int>(this->attackRow + 1, this->attackCol + 1);
}

void NaivePlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {}

bool NaivePlayer::hasFinishedAttacking() {
	return this->finishedAttacking;
}