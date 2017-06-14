#include "Player.h"	
#include <iostream>


Player::Player() :	
	attackRow(0),
	attackCol(0),
	finishedAttacking(false),
	isThereGoodAttack(false) {}

Player::~Player() {
	for (auto it = _instancesVec.begin(); it != _instancesVec.end(); ++it)
	{
		delete(*it);
	}
}


Coordinate Player::findNextAttack() {
	// TODO: Complete function!
	return Coordinate(-1, -1, -1);
}

//override function
void Player::setPlayer(int player) {
	this->playerNum = player;
}
//override function
void Player::setBoard(const BoardData& board) {
	this->player_board->loadBoard(board);
	this->boatsCount= this->player_board->getboatsCount;
	for (int i = 0; i<4;i++){
		if (boatsCount > 0){
			this->smallestBoat = i;
			break;
		}
	}
	this-> numberOfRows= this->player_board->rows();
	this-> numberOfCols= this->player_board->cols();
	this-> numberOfDepths= this->player_board->depth();
}
//override function
Coordinate Player::attack() {
	// TODO: Complete function!
		//first check if there is a good attack
	if (this->goodShots.size() > 0) {
		Coordinate attack = playGoodAttack();
		if (attack.row != -1 && attack.col != -1&& attack.depth != -1) {
			return attack;
		}
	}
	while (true){
	//starts with 0;
		int row = rand() % this->numberOfRows;
		int col = rand() % this->numberOfCols;
		int depth = rand() % this->numOfDepths;
		if (isValidToExplorationAttack (Coordinate (row,col,depth))){
			this->player_board->invalidateExplorationAttackArea(row,col,depth, this->smalestBoat);
			return Coordinate (row,col,depth);
		}
	}
}


//override function
void Player::notifyOnAttackResult(int player, Coordinate move, AttackResult result) {
////ask tal!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int row = move.row;
	int col = move.col;
	int depth = move.depth;

	player_board.setInvalidAttack(move);
	if (result == AttackResult::Sink) {
		this->player_board.setInvalidArea(move);
		if (player == this->playerNum) {
			if (this->currentAttack == 1) {
			//ask tal!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				this->player_board.setInvalidHorizontal(i - 1, j);
			}
			this->currentAttack = 0;
		}
		else{
			//think about it...
		}
	} 
	else if (result == AttackResult::Hit) {
		if (player == this->playerNum) {
			if (this->currentAttack == 0) {
				this->currentAttack = 1;
				setGoodShot(i + 1, j);
				setGoodShot(i, j + 1);
			}
			else if (this->currentAttack == 1) {
				this->player_board.setInvalidHorizontal(i - 1, j);
				this->player_board.setInvalidHorizontal(i, j);
				setGoodShot(i + 1, j);
				setGoodShot(i - 1, j);
			}
			else if (this->currentAttack == 2) {
				this->player_board.setInvalidVertical(i, j);
				setGoodShot(i, j + 1);
				setGoodShot(i, j - 1);
			}
		}
		else {
			setGoodShot(i + 1, j);
			setGoodShot(i - 1, j);
			setGoodShot(i, j + 1);
			setGoodShot(i, j - 1);
		}
	}
	else if (result == AttackResult::Miss) {
		if (player == this->playerNum) {
			if (this->currentAttack == 1) {
				this->currentAttack = 2;
			}
			else if (currentAttack == 2) {
				this->currentAttack = 0;
			}
		}
	}

}

//ask tal!!!
void Player::setGoodShot(int row, int col, int depth) {
	if (row < this->numOfRows && row >= 0 && col < this->numOfCols && col >= 0 && depth < this->numOfDepths && depth>=0) {
		if (this->player_board.isValidAttack(Coordinate(row, col, depth)) {
			this->goodShots.emplace_back(row, col, depth);
		}
	}
}

Coordinate Player::playGoodAttack() {
	Coordinate attack;
	while (this->goodShots.size() > 0) {
		attack = goodShots.front();
		goodShots.pop_front();
		if (player_board.isValidAttack(Coordinate (attack.row++, attack.col++, attack.depth))) {
			return attack;
			//return std::make_pair(attack.first+1, attack.second+1);
		}
	}
	return Coordinate(-1, -1, -1);
}

bool Player::hasFinishedAttacking() {
	return this->finishedAttacking;
}

IBattleshipGameAlgo* GetAlgorithm() {
	_instancesVec.push_back(new Player());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}
