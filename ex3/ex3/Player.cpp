#include "Player.h"	
#include <iostream>


Player::Player() :
	
	attackRow(0),
	attackCol(0),
	finishedAttacking(false),
	isThereGoodAttack(false) {}

Player::~Player() {}


Coordinate Player::findNextAttack() {
	// TODO: Complete function!


	return Coordinate(-1, -1, -1);
}

void Player::setPlayer(int player) {
	this->playerNum = player;
}
void Player::setBoard(const BoardData& board) {
	setProperties(player, numRows, numCols);
	this->player_board.loadBoard(board, player, this, numRows, numCols);
}
Coordinate Player::attack() {
	// TODO: Complete function!
		//first check if there is a good attack
	if (this->goodShots.size() > 0) {
		std::pair<int, int> attack = playGoodAttack();
		if (attack.first != -1 && attack.second != -1) {
			return attack;
		}
	}
	this->currentAttack = 0;
	while (this->attackRow < this->numOfRows) {
		while (this->attackCol < this->numOfCols) {
			if (player_board.isValidAttack(this->attackRow, this->attackCol)) {
				return std::make_pair(this->attackRow + 1, ++this->attackCol);
			}
			attackCol++;
		}
		this->attackCol = 0;
		this->attackRow++;
	}
	this->finishedAttacking = true;
	return Coordinate(-1, -1, -1);
}

bool Player::hasFinishedAttacking() {

	return this->finishedAttacking;
}

void Player::notifyOnAttackResult(int player, Coordinate move, AttackResult result) {
	int i = row - 1;
	int j = col - 1;
	player_board.setInvalidAttack(i, j);
	if (result == AttackResult::Sink) {
		this->player_board.setInvalidArea(i, j);
		if (player == this->playerNum) {
			if (this->currentAttack == 1) {
				this->player_board.setInvalidHorizontal(i - 1, j);
			}
			this->currentAttack = 0;
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

void Player::setGoodShot(int row, int col) {
	if (row < this->numOfRows && row >= 0 && col < this->numOfCols && col >= 0) {
		if (this->player_board.isValidAttack(row, col)) {
			this->goodShots.emplace_back(row, col);
		}
	}
}

std::pair<int, int> Player::playGoodAttack() {
	std::pair<int, int> attack;
	while (this->goodShots.size() > 0) {
		attack = goodShots.front();
		goodShots.pop_front();
		if (player_board.isValidAttack(attack.first++, attack.second++)) {
			return attack;
			//return std::make_pair(attack.first+1, attack.second+1);
		}
	}
	return std::make_pair(-1, -1);
}

IBattleshipGameAlgo* GetAlgorithm() {
	_instancesVec.push_back(new Player());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}

///////////////////////////////////////////////////////////////// smart player 


void SmartPlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	setProperties(player, numRows, numCols);
	this->player_board.loadBoard(board, player, this, numRows, numCols);

}

bool SmartPlayer::init(const std::string & path) {

	return true;
}

std::pair<int, int> SmartPlayer::attack() {
	//first check if there is a good attack
	if (this->goodShots.size() > 0) {
		std::pair<int, int> attack = playGoodAttack();
		if (attack.first != -1 && attack.second != -1) {
			return attack;
		}
	}
	this->currentAttack = 0;
	while (this->attackRow < this->numOfRows) {
		while (this->attackCol < this->numOfCols) {
			if (player_board.isValidAttack(this->attackRow, this->attackCol)) {
				return std::make_pair(this->attackRow + 1, ++this->attackCol);
			}
			attackCol++;
		}
		this->attackCol = 0;
		this->attackRow++;
	}
	this->finishedAttacking = true;
	return std::make_pair(-1, -1);
}

bool SmartPlayer::hasFinishedAttacking() {

	return this->finishedAttacking;
}

void SmartPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {
	int i = row - 1;
	int j = col - 1;
	player_board.setInvalidAttack(i, j);
	if (result == AttackResult::Sink) {
		this->player_board.setInvalidArea(i, j);
		if (player == this->playerNum) {
			if (this->currentAttack == 1) {
				this->player_board.setInvalidHorizontal(i - 1, j);
			}
			this->currentAttack = 0;
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

void SmartPlayer::setGoodShot(int row, int col) {
	if (row < this->numOfRows && row >= 0 && col < this->numOfCols && col >= 0) {
		if (this->player_board.isValidAttack(row, col)) {
			this->goodShots.emplace_back(row, col);
		}
	}
}

std::pair<int, int> SmartPlayer::playGoodAttack() {
	std::pair<int, int> attack;
	while (this->goodShots.size() > 0) {
		attack = goodShots.front();
		goodShots.pop_front();
		if (player_board.isValidAttack(attack.first++, attack.second++)) {
			return attack;
			//return std::make_pair(attack.first+1, attack.second+1);
		}
	}
	return std::make_pair(-1, -1);
}

IBattleshipGameAlgo* GetAlgorithm() {
	_instancesVec.push_back(new SmartPlayer());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}