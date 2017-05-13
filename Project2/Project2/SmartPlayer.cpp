
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

	this->player_board = NULL;
	this->attackRow = 0;
	this->attackCol =0;
	this->finishedAttacking= false;
	this->isThereGoodAttack= false;
	this->horizonalGoodAttack=0; //0 dont know, 1 horizontal, 2 the other direction...
	this->currentAttack = 0; // 1 up 2 down 3 left 4 right, 0 irrelevant
	this->down = <-1,-1>;
	this->up= <-1,-1>;
	this->left = <-1,-1>;
	this->right = <-1,-1>;
	this->playerNum = -1;
	this->numOfRows = -1;
	this->numOfCols = -1;
	result= NULL;

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

	return this->finishedAttacking;
}

void SmartPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	this-> result = result;
	handleAttackResult();
}

std::pair <int,int> SmartPlayer::playGoodAttack(){
	if (horizonalGoodAttack== 0){
		if (up.first != -1 && up.second != -1){
			this->currentAttack = 1;
			return up;
		}
		else {
			this->currentAttack = 2;
			return down;
		}
	}
	else if (horizonalGoodAttack == 1){
		if (left.first != -1 && left.second != -1){
			this->currentAttack = 3;
			return left;
		}
		else {
			this->currentAttack = 4;
			return right;
		}
	}
	else { // horizonalGoodAttack=2
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
	
	if (this->result == sunk){
		this->isThereGoodAttack = false;
		this ->up = <-1,-1>;
		this ->down = <-1,-1>;
		this ->left = <-1,-1>;
		this ->right = <-1,-1>;
		this->horizonalGoodAttack =0;
		this->currentAttack = 0;
	}
//if the attack hit:
//if there is an good attack then update the horizontal and the point and default the irrelevant points
// if no good attack - create good attack with horizontal 0 and the relevant points
	if (this->result == hit){
		if (this->isThereGoodAttack){
			if (this-> currentAttack ==1 ||this-> currentAttack ==2 ){
				this->horizonalGoodAttack = 2;
				this ->left = <-1,-1>;
				this ->right = <-1,-1>;
				if (this-> currentAttack ==1){
					if (this->attackRow > 0){
						this->up = <this->attackRow-1, this->attackCol>;
					}
					else{
						this ->up = <-1,-1>;
					}
				}
				else{
					if (this->attackRow < numRows){
						this->down = <this->attackRow+1, this->attackCol>;
					}
					else{
						this ->down = <-1,-1>;
					}
				}
			}
			else {
				this->horizonalGoodAttack = 1;
				this ->up = <-1,-1>;
				this ->down = <-1,-1>;
				if (this-> currentAttack ==3){
					if (this->attackCol > 0){
						this->left = <this->attackRow, this->attackCol-1>;
					}
					else{
						this ->left = <-1,-1>;
					}
				}
				else{
					if (this->attackCol < numRows){
						this->right = <this->attackRow, this->attackCol+1>;
					}
					else{
						this ->right = <-1,-1>;
					}
				}
			}

		}	
		else{
			this->isThereGoodAttack = true;
			this->horizonalGoodAttack = 0;	
			if (this->attackRow > 0){
				this->up = <this->attackRow-1, this->attackCol>;
			}
			else{
				this ->up = <-1,-1>;
			}
			if (this->attackRow < numRows){
				this->down = <this->attackRow+1, this->attackCol>;
			}
			else{
				this ->down = <-1,-1>;
			}

			if (this->attackCol < numRows){
				this->right = <this->attackRow, this->attackCol+1>;
			}
			else{
				this ->right = <-1,-1>;
			}
			if (this->attackCol > 0){
				this->left = <this->attackRow, this->attackCol-1>;
			}
			else{
				this ->left = <-1,-1>;
			}
		}
	}

//if miss:
//if there is no good attack - cool continue
//if there is a good attack -
//if horizontal 0- update the horizontal and the points
//else update the current point 

	else if (this->result == miss){
		if (this->isThereGoodAttack){
			if (this->horizonalGoodAttack==0){
				if (this->currentAttack ==1 || this->currentAttack ==2){
					this-> horizonalGoodAttack = 1;
					this ->left = <-1,-1>;
					this ->right = <-1,-1>;
				}
				else{
					this-> horizonalGoodAttack = 2;
					this ->up = <-1,-1>;
					this ->down = <-1,-1>;
				}
			}
		}
	}
}

IBattleshipGameAlgo* GetAlgorithm()
{
	_instancesVec.push_back(new SmartPlayer());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}