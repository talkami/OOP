
#include "SmartPlayer.h"
#include <iostream>

SmartPlayer::SmartPlayer() :
	CommonPlayer(),
	attackRow(0),
	attackCol(0),
	finishedAttacking(false) {}

SmartPlayer::~SmartPlayer() {}

void SmartPlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	this->playerNum = player;
	this->numOfRows = numRows;
	this->numOfCols = numCols;
	this->player_board.loadBoard(board, player, this, numRows, numCols);

}

bool SmartPlayer::init(const std::string & path) {

	//CREATE FUNCTION!!!!!

	return true;
}

std::pair<int, int> SmartPlayer::attack() {
	
	while (!player_board.isValidAttack(this->attackRow, this->attackCol)) {
		if (this->attackCol < numOfCols-2) {
			this->attackCol= this->attackCol+2;
		}
		else {
			if (this->attackRow < numOfRows - 2) {
				this->attackCol = attackCol%2;
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

	return std::pair<int, int>(-1,-1);
}

bool SmartPlayer::hasFinishedAttacking() {

	//FUNCTION MAY NEED CORRECTING
	return this->finishedAttacking;
}

void SmartPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	//COMPLETE FUNCTION!!!
}
