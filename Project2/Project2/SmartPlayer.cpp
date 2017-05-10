
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
	//first check if there is a good attack
	if (this-> isThereGoodAttack){
		return playGoodAttack();
	}
	this->currentAttack = 0;
	//go on the board in jumps of 2, where each line the starting point switch between 0,1
	while (this->attackRow < this->numOfRows) {
		while (this->attackCol < this->numOfCols-1) {
			if (player_board.isValidAttack(this->attackRow, this->attackCol)) {
				return std::pair<int, int>(this->attackRow + 1, ++this->attackCol);
			}
			attackCol++;
		}
		this->attackRow++;
		this->attackCol = 0+ attackRow%2;
	}
	this->finishedAttacking = true;
	return std::pair<int, int>(-1, -1);
}

bool SmartPlayer::hasFinishedAttacking() {

	//FUNCTION MAY NEED CORRECTING
	return this->finishedAttacking;
}

void SmartPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	//COMPLETE FUNCTION!!!
}
AttackResult SmartPayer::getFormerAttackResult (){

}

void SmartPlayer:: handleAttackResult (AttackResult result, pair<int, int> lastAttack){
//if the boat has sunk no good attack is needed and all the relevant vals go to default
	

//if the attack hit:
//if there is an good attack then update the horizontal and the point and default the irrelevant points
// if no good attack - create good attack with horizontal 0 and the relevant points

//if miss:
//if there is no good attack - cool continue
//if there is a good attack -
//if horizontal 0- update the horizontal and the points
//else update the current point 

}

pair <int,int> SmartPlayer:: playGoodAttack(){
	if (horizonalGoodAttack== 0){
		if (up != <-1,-1>){
			this->currentAttack = 1;
			return up;
		}
		else {
			this->currentAttack = 2;
			return down;
		}
	}
	else if (horizonalGoodAttack == 1){
		if (left != <-1,-1>){
			this->currentAttack = 3;
			return left;
		}
		else {
			this->currentAttack = 4;
			return right;
		}
	}
	else { // horizonalGoodAttack=2
		if (up != <-1,-1>){
			this->currentAttack = 1;
			return up;
		}
		else {
			this->currentAttack = 2;
			return down;
		}
	}
}