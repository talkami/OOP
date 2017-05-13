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
	this->player_board.loadBoard(board, player, this, numRows, numCols);
}

bool NaivePlayer::init(const std::string & path) {

	this->player_board = NULL;
	this->attackRow = 0;
	this->attackCol = 0;
	this->finishedAttacking = false;
	this->playerNum = -1;
	this->numOfRows = -1;
	this->numOfCols = -1;

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


IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new NaivePlayer());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}