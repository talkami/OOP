#include "Player.h"	
#include <iostream>
#include <algorithm>
#include <ctime>

//override function
void Player::setPlayer(int player) {
	this->playerNum = player;
}

//override function
void Player::setBoard(const BoardData& board) {
	this->player_board->loadBoard(board, this->playerNum);

	for (int depth = 0; depth < this->player_board->depth(); depth++) {
		for (int row = 0; row < this->player_board->rows(); row++) {
			for (int col = 0; col < this->player_board->cols(); col++) {
				this->possibleAttacks.push_back(Coordinate(row, col, depth));
			}
		}
	}
	srand(unsigned(time(NULL)));
	std::random_shuffle(this->possibleAttacks.begin(), this->possibleAttacks.end());
}

//override function
Coordinate Player::attack() {
	if (this->goodShots.size() > 0) {
		Coordinate attack = findGoodAttack();
		if (attack.row != -1 && attack.col != -1 && attack.depth != -1) {
			return Coordinate(attack.row + 1, attack.col + 1, attack.depth + 1);
		}
	}
	while (!(possibleAttacks.empty())){
		Coordinate coor = this->possibleAttacks.back();
		this->possibleAttacks.pop_back();
		if (this->player_board->isValidAttack(coor)) {
			return Coordinate(coor.row + 1, coor.col + 1, coor.depth + 1);
		}
	}
	return Coordinate(-1, -1, -1);
}

void Player::notifyOnAttackResult(int player, Coordinate move, AttackResult result) {
	this->player_board->setInvalidAttack(move);
	if (player == playerNum) {
		if (result == AttackResult::Miss) {
			this->attackDir = 0;
		}
		else if (result == AttackResult::Sink) {
			this->player_board->setInvalidArea(move);
			this->attackDir = 0;
			this->lastHit = Coordinate(-1, -1, -1);
		}
		else if (result == AttackResult::Hit) {
			if (this->attackDir == 1) {
				this->player_board->setInvalidVertical(move);
				this->player_board->setInvalidVertical(this->lastHit);
				this->player_board->setInvalidDepth(move);
				this->player_board->setInvalidDepth(this->lastHit);
			}
			else if (this->attackDir == 2) {
				this->player_board->setInvalidHorizontal(move);
				this->player_board->setInvalidHorizontal(this->lastHit);
				this->player_board->setInvalidDepth(move);
				this->player_board->setInvalidDepth(this->lastHit);
			}
			else if (this->attackDir == 3) {
				this->player_board->setInvalidVertical(move);
				this->player_board->setInvalidVertical(this->lastHit);
				this->player_board->setInvalidHorizontal(move);
				this->player_board->setInvalidHorizontal(this->lastHit);
			}
			this->lastHit = move;
		}
	}
}

void Player::setAttackArea(int row, int col, int depth) {
	this->goodShots.emplace_back(Coordinate(row - 1, col, depth));
	this->goodShots.emplace_back(Coordinate(row + 1, col, depth));
	this->goodShots.emplace_back(Coordinate(row, col - 1, depth));
	this->goodShots.emplace_back(Coordinate(row, col + 1, depth));
	this->goodShots.emplace_back(Coordinate(row, col, depth - 1));
	this->goodShots.emplace_back(Coordinate(row, col, depth + 1));
}

Coordinate Player::findGoodAttack() {
	Coordinate attack = Coordinate(-1, -1, -1);
	while (this->goodShots.size() > 0) {
		attack = goodShots.front();
		goodShots.pop_front();
		if (player_board->isValidAttack(attack)) {
			if (attack.row == this->lastHit.row + 1 || attack.row == this->lastHit.row - 1) {
				this->attackDir = 1;
			}
			else if (attack.col == this->lastHit.col + 1 || attack.col == this->lastHit.col - 1) {
				this->attackDir = 2;
			}
			else if (attack.depth == this->lastHit.depth + 1 || attack.depth == this->lastHit.depth - 1) {
				this->attackDir = 3;
			}

			return attack;
		}
	}
	this->attackDir = 0;
	return Coordinate(-1, -1, -1);
}

IBattleshipGameAlgo* GetAlgorithm() {
	return new Player();
}
