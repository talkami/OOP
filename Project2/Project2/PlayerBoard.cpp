#include "PlayerBoard.h"
#include <string>
#include <fstream>
#include <iostream>



bool PlayerBoard::loadBoard(const char** board, int player, CommonPlayer* owner, int rows, int cols) {
	bool result = true;
	this->numOfRows = rows;
	this->numOfCols = cols;
	setVars();

	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			setPoint(i,j);
		}
	}
	setBoard(board, player, owner);

	return result;
}

void PlayerBoard::setBoard(const char** board, int player, CommonPlayer* owner) {
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			char c = board[i][j];
			if ((c == 'B' + 32 * player) || (c == 'P' + 32 * player) || 
				(c == 'M' + 32 * player) || (c == 'D' + 32 * player)) {
				if (c == 'B' + 32 * player) {
					addBoatToBoard(this->matrix[i][j], 1, player, owner, nullptr);
				}
				else if (c == 'P' + 32 * player) {
					addBoatToBoard(this->matrix[i][j], 2, player, owner, nullptr);
				}
				else if (c == 'M' + 32 * player) {
					addBoatToBoard(this->matrix[i][j], 3, player, owner, nullptr);
				}
				else if (c == 'D' + 32 * player) {
					addBoatToBoard(this->matrix[i][j], 4, player, owner, nullptr);
				}
				setInvalidArea(this->matrix[i][j]);
			}
		}
	}



}

void PlayerBoard::setInvalidArea(Point* point) {
	point->setInvalidAttack();
	if (point->getUp()) {
		point->getUp()->setInvalidAttack();
	}
	if (point->getLeft()) {
		point->getLeft()->setInvalidAttack();
	}
	if (point->getRight()) {
		point->getRight()->setInvalidAttack();
	}
	if (point->getDown()) {
		point->getDown()->setInvalidAttack();
	}
}


bool PlayerBoard::updateBoardAfterAttack(int row, int col, AttackResult result) {
	//COMPLETE FUCTION!!!!

	return true;
}

void PlayerBoard::setInvalidAttack(int row, int col) {
	this->matrix[row][col]->setInvalidAttack();
}

bool PlayerBoard::isValidAttack(int row, int col) {
	return this->matrix[row][col]->isValidAttack();
}