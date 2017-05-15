#include "PlayerBoard.h"

bool PlayerBoard::loadBoard(const char** board, int player, CommonPlayer* owner, int rows, int cols) {
	bool result = true;
	this->numOfRows = rows;
	this->numOfCols = cols;
	setVars();

	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			setPoint(i, j);
		}
	}
	setBoard(board, player, owner);

	return result;
}

void PlayerBoard::setBoard(const char** board, int player, CommonPlayer* owner) {
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			char c = board[i][j];
			if (c == 'B' || c == 'b') {
				addBoatToBoard(this->matrix[i][j], 1, player, owner, nullptr);
				this->matrix[i][j]->setInvalidAttack();
				setInvalidArea(this->matrix[i][j]);
			}
			else if (c == 'P' || c == 'p') {
				addBoatToBoard(this->matrix[i][j], 2, player, owner, nullptr);
				this->matrix[i][j]->setInvalidAttack();
				setInvalidArea(this->matrix[i][j]);
			}
			else if (c == 'M' || c == 'm') {
				addBoatToBoard(this->matrix[i][j], 3, player, owner, nullptr);
				this->matrix[i][j]->setInvalidAttack();
				setInvalidArea(this->matrix[i][j]);
			}
			else if (c == 'D' || c == 'd') {
				addBoatToBoard(this->matrix[i][j], 4, player, owner, nullptr);
				this->matrix[i][j]->setInvalidAttack();
				setInvalidArea(this->matrix[i][j]);
			}
		}
	}
}

void PlayerBoard::setInvalidHorizontal(Point* point) {
	if (point->getLeft()) {
		point->getLeft()->setInvalidAttack();
	}
	if (point->getRight()) {
		point->getRight()->setInvalidAttack();
	}
}

void PlayerBoard::setInvalidVertical(Point* point) {
	if (point->getUp()) {
		point->getUp()->setInvalidAttack();
	}
	if (point->getDown()) {
		point->getDown()->setInvalidAttack();
	}
}

void PlayerBoard::setInvalidArea(Point* point) {
	setInvalidHorizontal(point);
	setInvalidVertical(point);
}

void PlayerBoard::setInvalidHorizontal(int row, int col) {
	setInvalidHorizontal(this->matrix[row][col]);
}

void PlayerBoard::setInvalidVertical(int row, int col) {
	setInvalidVertical(this->matrix[row][col]);
}

void PlayerBoard::setInvalidArea(int row, int col) {
	setInvalidArea(this->matrix[row][col]);
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