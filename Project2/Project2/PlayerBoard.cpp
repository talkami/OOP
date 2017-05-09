#include "PlayerBoard.h"
#include <string>
#include <fstream>
#include <iostream>


PlayerBoard::~PlayerBoard() {
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			delete this->matrix[i][j];
		}
	}

	for (int i = 0; i<this->numOfRows; i++) {
		delete[]this->matrix[i];
		delete[]this->playerABoard[i];
		delete[]this->playerBBoard[i];
	}
	delete[]this->matrix;
	delete[]this->playerABoard;
	delete[]this->playerBBoard;
}

//load PlayerBoard function
bool PlayerBoard::loadBoard(const std::string& boardFile, CommonPlayer* A, CommonPlayer* B, int rows, int cols) {
	bool result = true;
	this->numOfRows = rows;
	this->numOfCols = cols;
	setVars(false);

	std::ifstream fin(boardFile);
	if (!fin) {
		std::cout << "Error reading from file: " << boardFile << std::endl;
		return false;
	}

	for (int i = 0; i < rows; i++) {
		std::string buffer;
		std::getline(fin, buffer);
		for (int j = 0; j < cols; j++) {
			char currChar = ' ';
			if (j < buffer.length()) {
				currChar = buffer.at(j);
			}
			createBoard(currChar, A, B, i, j);
		}
	}

	checkBoatValidity();
	result = checkBoard();
	result = (checkNumOfPlayersBoats(A, B) && result);

	if (this->errorArray[8]) {
		result = false;
		std::cout << "Adjacent Ships on PlayerBoard" << std::endl;
	}
	return result;
}

bool PlayerBoard::playerLoadBoard(const char** playerPlayerBoard, CommonPlayer* player, int rows, int cols) {
	bool result = true;
	this->numOfRows = rows;
	this->numOfCols = cols;
	setVars(true);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			createBoard(playerPlayerBoard[i][j], player, nullptr, rows, cols);
		}
	}

	return result;
}

void PlayerBoard::setVars(bool isPlayerPlayerBoard) {
	this->matrix = new Point**[this->numOfRows];
	if (!isPlayerPlayerBoard) {
		this->playerABoard = new char *[this->numOfRows];
		this->playerBBoard = new char *[this->numOfRows];
	}

	for (int i = 0; i < this->numOfRows; i++) {
		this->matrix[i] = new Point*[this->numOfCols];
		if (!isPlayerPlayerBoard) {
			this->playerABoard[i] = new char[this->numOfCols];
			this->playerBBoard[i] = new char[this->numOfCols];
		}
	}

	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			this->matrix[i][j] = new Point();
			this->matrix[i][j]->setX(i);
			this->matrix[i][j]->setY(j);
		}
	}
}

void PlayerBoard::createBoard(char currentChar, CommonPlayer* A, CommonPlayer* B, int row, int col) {
	// putting up the points- checking if the left/ up to the current point have a boat in it, and by that updating the "NEAR" variable
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
	addToPlayerBoard(currentChar, row, col, A, B);
}

//checking the char read from the file and putting the boats on the PlayerBoard
void PlayerBoard::addToPlayerBoard(char currentChar, int row, int col, CommonPlayer* A, CommonPlayer* B) {

	if (currentChar == 'B') {
		if (A != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 1, 0, A, B);
			this->playerABoard[row][col] = 'B';
			this->playerBBoard[row][col] = ' ';
		}
	}
	else if (currentChar == 'b') {
		if (B != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 1, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'b';
		}
	}
	else if (currentChar == 'P') {
		if (A != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 2, 0, A, B);
			this->playerABoard[row][col] = 'P';
			this->playerBBoard[row][col] = ' ';
		}
	}
	else if (currentChar == 'p') {
		if (B != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 2, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'p';
		}
	}
	else if (currentChar == 'M') {
		if (A != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 3, 0, A, B);
			this->playerABoard[row][col] = 'M';
			this->playerBBoard[row][col] = ' ';
		}
	}
	else if (currentChar == 'm') {
		if (B != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 3, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'm';
		}
	}
	else if (currentChar == 'D') {
		if (A != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 4, 0, A, B);
			this->playerABoard[row][col] = 'D';
			this->playerBBoard[row][col] = ' ';
		}
	}
	else if (currentChar == 'd') {
		if (B != nullptr) {
			addBoatToBoard(this->matrix[row][col], row, col, 4, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'd';
		}
	}
	else {
		if (A != nullptr && B != nullptr) {
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = ' ';
		}
	}
}

//checking that all boats are of correct size and shape
void PlayerBoard::checkBoatValidity() {
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

bool PlayerBoard::checkBoard() {
	bool result = true;

	if (this->errorArray[0]) {
		std::cout << "Wrong size or shape for ship B for player A" << std::endl;
		result = false;
	}
	if (this->errorArray[1]) {
		std::cout << "Wrong size or shape for ship P for player A" << std::endl;
		result = false;
	}
	if (this->errorArray[2]) {
		std::cout << "Wrong size or shape for ship M for player A" << std::endl;
		result = false;
	}
	if (this->errorArray[3]) {
		std::cout << "Wrong size or shape for ship D for player A" << std::endl;
		result = false;
	}
	if (this->errorArray[4]) {
		std::cout << "Wrong size or shape for ship b for player B" << std::endl;
		result = false;
	}
	if (this->errorArray[5]) {
		std::cout << "Wrong size or shape for ship p for player B" << std::endl;
		result = false;
	}
	if (this->errorArray[6]) {
		std::cout << "Wrong size or shape for ship m for player B" << std::endl;
		result = false;
	}
	if (this->errorArray[7]) {
		std::cout << "Wrong size or shape for ship d for player B" << std::endl;
		result = false;
	}
	return result;
}

//checking each player have the right amount of boats
bool PlayerBoard::checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B) {
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


bool PlayerBoard::updateBoardAfterAttack(Point * point, AttackResult result) {
	//COMPLETE FUCTION!!!!

	return true;
}


// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
AttackResult PlayerBoard::play_attack(std::pair<int, int> attack, int attacker, bool* selfHit) {
	if (attack.first == -1 || attack.second == -1) {
		return AttackResult::Miss;
	}
	int x = attack.first - 1;
	int y = attack.second - 1;
	AttackResult result = matrix[x][y]->attack(attacker, selfHit);
	return result;
}


char** PlayerBoard::getPlayerABoard() {
	return this->playerABoard;
}
char** PlayerBoard::getPlayerBBoard() {
	return this->playerBBoard;
}

//inner function helping the loadPlayerBoard. pretty much useless outside.
void PlayerBoard::addBoatToBoard(Point* point, int i, int j, int size, int player, CommonPlayer* owner, CommonPlayer* rival) {
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


void PlayerBoard::setInvalidAttack(int row, int col) {
	this->matrix[row - 1][col - 1]->invalidToAttack();
}


void PlayerBoard::checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival) {

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

bool PlayerBoard::isValidAttack(int row, int col) {
	return this->matrix[row - 1][col - 1]->isValidToAttack();
}