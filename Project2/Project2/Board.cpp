#include "Board.h"
#include <string>
#include <fstream>
#include <iostream>


Board::~Board() {
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			delete this->matrix[i][j];
		}
		delete[]this->matrix[i];
	}

	delete[]this->matrix;
}

void Board::setPoint(int row, int col) {
	if (row>0) {
		this->matrix[row][col]->setUp(this->matrix[row - 1][col]);
		this->matrix[row - 1][col]->setDown(this->matrix[row][col]);
		if (this->matrix[row - 1][col]->getBoat() != nullptr) {
			this->matrix[row][col]->setNear(true);
		}
	}
	if (col>0) {
		this->matrix[row][col]->setLeft(this->matrix[row][col - 1]);
		this->matrix[row][col - 1]->setRight(this->matrix[row][col]);
		if (this->matrix[row][col - 1]->getBoat() != nullptr) {
			this->matrix[row][col]->setNear(true);
		}
	}
}

void Board::setVars() {
	this->matrix = new Point**[this->numOfRows];

	for (int i = 0; i < this->numOfRows; i++) {
		this->matrix[i] = new Point*[this->numOfCols];
		for (int j = 0; j < this->numOfCols; j++) {
					this->matrix[i][j] = new Point();
					this->matrix[i][j]->setX(i);
					this->matrix[i][j]->setY(j);
				}
	}
}
/*
//checking that all boats are of correct size and shape
void Board::checkBoatValidity() {
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			Boat* boat = this->matrix[i][j]->getBoat();
			if (boat != nullptr) {
				if ((boat->getBoatSize() != boat->getAcctualSize()) || !boat->isValid()) {
					int errorNum = (boat->getBoatSize() - 1) + (4 * boat->getPlayer());
					errorArray[errorNum] = true;
					if (boat->getRival() != nullptr) {
						boat->getOwner()->removeBoat();
					}
					delete boat;
				}
			}
		}
	}
}

bool Board::checkBoard() {
	bool result = true;

	if (errorArray[0]) {
		std::cout << "Wrong size or shape for ship B for player A" << std::endl;
		result = false;
	}
	if (errorArray[1]) {
		std::cout << "Wrong size or shape for ship P for player A" << std::endl;
		result = false;
	}
	if (errorArray[2]) {
		std::cout << "Wrong size or shape for ship M for player A" << std::endl;
		result = false;
	}
	if (errorArray[3]) {
		std::cout << "Wrong size or shape for ship D for player A" << std::endl;
		result = false;
	}
	if (errorArray[4]) {
		std::cout << "Wrong size or shape for ship b for player B" << std::endl;
		result = false;
	}
	if (errorArray[5]) {
		std::cout << "Wrong size or shape for ship p for player B" << std::endl;
		result = false;
	}
	if (errorArray[6]) {
		std::cout << "Wrong size or shape for ship m for player B" << std::endl;
		result = false;
	}
	if (errorArray[7]) {
		std::cout << "Wrong size or shape for ship d for player B" << std::endl;
		result = false;
	}
	return result;
}

//checking each player have the right amount of boats
bool Board::checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B) {
	bool result = true;
	if (A != nullptr) {
		int numOfBoatsA = A->getNumOfBoats();
		if (numOfBoatsA < 5) {
			result = false;
			std::cout << "Too few ships for player A" << std::endl;
		}
		if (numOfBoatsA > 5) {
			result = false;
			std::cout << "Too many ships for player A" << std::endl;
		}
	}
	if (B != nullptr) {
		int numOfBoatsB = B->getNumOfBoats();
		if (numOfBoatsB < 5) {
			result = false;
			std::cout << "Too few ships for player B" << std::endl;
		}
		if (numOfBoatsB > 5) {
			result = false;
			std::cout << "Too many ships for player B" << std::endl;
		}
	}
	return result;
}


bool Board::updateBoardAfterAttack(Point * point, AttackResult result) {
	//COMPLETE FUCTION!!!!

	return true;
}


// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
AttackResult Board::play_attack(std::pair<int, int> attack, int attacker, bool* selfHit) {
	int x = attack.first - 1;
	int y = attack.second - 1;
	AttackResult result = matrix[x][y]->attack(attacker, selfHit);
	return result;
}

//inner function helping the loadBoard. pretty much useless outside.
void Board::addBoatToBoard(Point* point, int i, int j, int size, int player, CommonPlayer* owner, CommonPlayer* rival) {
	//if no boat near the current point
	if (!point->getNear()) {
		Boat* boat = new Boat(size, player, owner, rival, point);
		point->setBoat(boat);
	}
	//if there is boat near the current point
	else {
		if (i > 0) {
			Boat* boat = point->getUp()->getBoat();
			if (boat != nullptr) {
				checkAdjacentBoat(boat, point, size, 1, player, owner, rival);
			}
		}

		if (j > 0) {
			Boat* boat = point->getLeft()->getBoat();
			if (boat != nullptr) {
				checkAdjacentBoat(boat, point, size, 2, player, owner, rival);
			}
		}
	}
}


void Board::setInvalidAttack(int row, int col) {
	this->matrix[row - 1][col - 1]->invalidToAttack();
}


void Board::checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival) {

	if (boat->getBoatSize() == size && (boat->getHorizontal() == horizontal || boat->getHorizontal() == 0) && boat->getAcctualSize() < size && boat->getPlayer() == player) {
		boat->addPoint(point);
		boat->setHorizontal(horizontal);
		if (point->getBoat() != nullptr) {
			if (!point->getBoat()->isValid()) {
				boat->setValid(false);
			}
			else {
				delete point->getBoat();
			}
			owner->removeBoat();
		}
		point->setBoat(boat);
	}
	else {
		if (boat->getBoatSize() != size || boat->getPlayer() != player) {
			if (point->getBoat() != nullptr) {
				this->errorArray[8] = true;
				return;
			}
			Boat* newBoat = new Boat(size, player, owner, rival, point);
			point->setBoat(newBoat);
			this->errorArray[8] = true;
			return;
		}
		else {
			if ((point->getBoat() != nullptr) && (point->getBoat() != boat)) {
				delete point->getBoat();
				owner->removeBoat();
			}
			boat->setValid(false);
			boat->addPoint(point);
			point->setBoat(boat);
			return;
		}
	}
}

bool Board::isValidAttack(int row, int col) {
	return this->matrix[row - 1][col - 1]->isValidToAttack();
}
*/