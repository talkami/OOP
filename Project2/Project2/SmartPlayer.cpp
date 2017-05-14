
#include "SmartPlayer.h"
#include <iostream>

SmartPlayer::SmartPlayer() :
	CommonPlayer(),
	attackRow(0),
	attackCol(0),
	finishedAttacking(false),
	isThereGoodAttack(false){}

SmartPlayer::~SmartPlayer() {}

void SmartPlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	setProperties(player, numRows, numCols);
	this->player_board.loadBoard(board, player, this, numRows, numCols);

}

bool SmartPlayer::init(const std::string & path) {

	return true;
}

std::pair<int, int> SmartPlayer::attack() {
	//first check if there is a good attack
	if (this-> isThereGoodAttack){
		return playGoodAttack();
	}
	this->currentAttack = 0;
	while (this->attackRow < this->numOfRows) {
		while (this->attackCol < this->numOfCols-1) {
			if (player_board.isValidAttack(this->attackRow, this->attackCol)) {
				return std::pair<int, int>(this->attackRow + 1, ++this->attackCol);
			}
			attackCol++;
		}
		this->attackRow++;
	}
	this->finishedAttacking = true;
	return std::pair<int, int>(-1, -1);
}

bool SmartPlayer::hasFinishedAttacking() {

	return this->finishedAttacking;
}

void SmartPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	player_board.setInvalidAttack(row, col);
	if (result == AttackResult::Sink) {
		this->player_board.setInvalidArea(row, col);
	}
	else if (result == AttackResult::Hit) {

	}else{

	}
	this-> result = result;
	handleAttackResult();
}

std::pair<int,int> SmartPlayer::playGoodAttack(){
	if (horizonalGoodAttack == 1){
		if (left.first != -1 && left.second != -1){
			this->currentAttack = 3;
			return left;
		}
		else {
			this->currentAttack = 4;
			return right;
		}
	}
	else { 
		if (left.first != -1 && left.second != -1){
			this->currentAttack = 1;
			return up;
		}
		else {
			this->currentAttack = 2;
			return down;
		}
	}
}
void SmartPlayer::handleAttackResult (){
//if the boat has sunk no good attack is needed and all the relevant vals go to default
	
	if (this->result == AttackResult::Sink){
		this->isThereGoodAttack = false;
		this ->up = std::pair<int, int>(-1, -1);
		this ->down = std::pair<int, int>(-1, -1);
		this ->left = std::pair<int, int>(-1, -1);
		this ->right = std::pair<int, int>(-1, -1);
		this->horizonalGoodAttack =0;
		this->currentAttack = 0;
	}
//if the attack hit:
//if there is an good attack then update the horizontal and the point and default the irrelevant points
// if no good attack - create good attack with horizontal 0 and the relevant points
	if (this->result == AttackResult::Hit){
		if (this->isThereGoodAttack){
			if (this-> currentAttack ==1 ||this-> currentAttack ==2 ){
				this->horizonalGoodAttack = 2;
				this ->left = std::pair<int, int>(-1, -1);
				this ->right = std::pair<int, int>(-1, -1);
				if (this-> currentAttack ==1){
					if (this->attackRow > 0){
						this->up = std::pair<int, int>(this->attackRow-1, this->attackCol);
					}
					else{
						this ->up = std::pair<int, int>(-1, -1);
					}
				}
				else{
					if (this->attackRow <  this->numOfRows){
						this->down = std::pair<int, int>(this->attackRow+1, this->attackCol);
					}
					else{
						this ->down = std::pair<int, int>(-1, -1);
					}
				}
			}
			else {
				this->horizonalGoodAttack = 1;
				this ->up = std::pair<int, int>(-1, -1);
				this ->down = std::pair<int, int>(-1, -1);
				if (this-> currentAttack ==3){
					if (this->attackCol > 0){
						this->left = std::pair<int, int>(this->attackRow, this->attackCol-1);
					}
					else{
						this ->left = std::pair<int, int>(-1, -1);
					}
				}
				else{
					if (this->attackCol <  this->numOfRows){
						this->right = std::pair<int, int>(this->attackRow, this->attackCol+1);
					}
					else{
						this ->right = std::pair<int, int>(-1, -1);
					}
				}
			}

		}	
		else{
			this->isThereGoodAttack = true;
			this->horizonalGoodAttack = 0;	
			if (this->attackRow > 0){
				this->up = std::pair<int, int>(this->attackRow-1, this->attackCol);
			}
			else{
				this ->up = std::pair<int, int>(-1, -1);
			}
			if (this->attackRow <  this->numOfRows){
				this->down = std::pair<int, int>(this->attackRow+1, this->attackCol);
			}
			else{
				this ->down = std::pair<int, int>(-1, -1);
			}

			if (this->attackCol <  this->numOfRows){
				this->right = std::pair<int, int>(this->attackRow, this->attackCol+1);
			}
			else{
				this ->right = std::pair<int, int>(-1, -1);
			}
			if (this->attackCol > 0){
				this->left = std::pair<int, int>(this->attackRow, this->attackCol-1);
			}
			else{
				this ->left = std::pair<int, int>(-1, -1);
			}
		}
	}

//if miss:
//if there is no good attack - cool continue
//if there is a good attack -
//if horizontal 0- update the horizontal and the points
//else update the current point 

	else if (this->result == AttackResult::Miss){
		if (this->isThereGoodAttack){
			if (this->horizonalGoodAttack==0){
				if (this->currentAttack ==1 || this->currentAttack ==2){
					this-> horizonalGoodAttack = 1;
					this->left = std::pair<int, int>(-1, -1);
					this->right = std::pair<int, int>(-1, -1);
				}
				else{
					this-> horizonalGoodAttack = 2;
					this->up = std::pair<int, int>(-1, -1);
					this->down = std::pair<int, int>(-1, -1);
				}
			}
		}
	}
}

/*IBattleshipGameAlgo* GetAlgorithm(){
	_instancesVec.push_back(new SmartPlayer());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}*/