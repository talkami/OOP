#include "GameBoard.h"
#include <string>
#include <fstream>
#include <iostream>


GameBoard::~GameBoard() {
	for (int i = 0; i < this->numOfRows; i++) {
		delete[]this->playerABoard[i];
		delete[]this->playerBBoard[i];
	}
	delete[]this->playerABoard;
	delete[]this->playerBBoard;
}

bool GameBoard::initBoard(const std::string& path, CommonPlayer* A, CommonPlayer* B, int rows, int cols) {
	bool result = true;
	this->numOfRows = rows;
	this->numOfCols = cols;
	std::string errorPath;
	if (path == ".") {
		errorPath = "Working Directory";
	}
	else {
		errorPath = path;
	}

	SeaBattleBoardLister boardFileLister = SeaBattleBoardLister(path);
	if (boardFileLister.getFilesList().size() == 0) {
		std::cout << "Missing board file (*.sboard) looking in path: " << errorPath << std::endl;
		result = false;
	}
	if (result) {
		result = loadBoard(boardFileLister.getFilesList()[0], A, B);
	}
	return result;
}

//load GameBoard function
bool GameBoard::loadBoard(const std::string& boardFile, CommonPlayer* A, CommonPlayer* B) {
	bool result = true;
	setVars();

	std::ifstream fin(boardFile);
	if (!fin) {
		std::cout << "Error reading from file: " << boardFile << std::endl;
		return false;
	}

	for (int i = 0; i < this->numOfRows; i++) {
		std::string buffer;
		std::getline(fin, buffer);
		for (int j = 0; j < this->numOfCols; j++) {
			char currChar = ' ';
			if (j < buffer.length()) {
				currChar = buffer.at(j);
			}
			setPoint(i, j);
			addToPlayerBoard(currChar, i, j, A, B);
		}
	}

	checkBoatValidity();
	result = checkBoard();
	result = (checkNumOfPlayersBoats(A, B) && result);

	if (this->errorArray[8]) {
		result = false;
		std::cout << "Adjacent Ships on Board" << std::endl;
	}
	return result;
}

void GameBoard::setVars() {
	Board::setVars();

	this->playerABoard = new char *[this->numOfRows];
	this->playerBBoard = new char *[this->numOfRows];

	for (int i = 0; i < this->numOfRows; i++) {
		this->playerABoard[i] = new char[this->numOfCols];
		this->playerBBoard[i] = new char[this->numOfCols];
		memset(playerABoard[i], ' ', numOfCols);
		memset(playerBBoard[i], ' ', numOfCols);
	}

}


//checking the char read from the file and putting the boats on the GameBoard
void GameBoard::addToPlayerBoard(char currentChar, int row, int col, CommonPlayer* A, CommonPlayer* B) {

	if (currentChar == 'B') {
		addBoatToBoard(this->matrix[row][col], 1, 0, A, B);
		this->playerABoard[row][col] = 'B';
	}
	else if (currentChar == 'b') {
		addBoatToBoard(this->matrix[row][col], 1, 1, B, A);
		this->playerBBoard[row][col] = 'b';
	}
	else if (currentChar == 'P') {
		addBoatToBoard(this->matrix[row][col], 2, 0, A, B);
		this->playerABoard[row][col] = 'P';
	}
	else if (currentChar == 'p') {
		addBoatToBoard(this->matrix[row][col],  2, 1, B, A);
		this->playerBBoard[row][col] = 'p';
	}
	else if (currentChar == 'M') {
		addBoatToBoard(this->matrix[row][col], 3, 0, A, B);
		this->playerABoard[row][col] = 'M';
	}
	else if (currentChar == 'm') {
		addBoatToBoard(this->matrix[row][col], 3, 1, B, A);
		this->playerBBoard[row][col] = 'm';
	}
	else if (currentChar == 'D') {
		addBoatToBoard(this->matrix[row][col], 4, 0, A, B);
		this->playerABoard[row][col] = 'D';
	}
	else if (currentChar == 'd') {
		addBoatToBoard(this->matrix[row][col], 4, 1, B, A);
		this->playerBBoard[row][col] = 'd';
	}
}

void GameBoard::addBoatToBoard(Point* point, int size, int player, CommonPlayer* owner, CommonPlayer* rival) {
	if (!point->getNear()) {
		//there is no boat adjacent to current point
		Boat* boat = new Boat(size, player, owner, rival, point);
		point->setBoat(boat);
	}
	else {
		//there is a boat adjacent to current point
		if (point->getX() > 0) {
			Boat* boat = point->getUp()->getBoat();
			if (boat != nullptr) {
				//there is a boat above current point 
				checkAdjacentBoat(boat, point, size, 1, player, owner, rival);
			}
		}

		if (point->getY() > 0) {
			Boat* boat = point->getLeft()->getBoat();
			if (boat != nullptr) {
				//there is a boat left of current point
				checkAdjacentBoat(boat, point, size, 2, player, owner, rival);
			}
		}
	}
}

void GameBoard::checkAdjacentBoat(Boat* boat, Point* point, int size, int horizontal, int player, CommonPlayer* owner, CommonPlayer* rival) {

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

//checking that all boats are of correct size and shape
void GameBoard::checkBoatValidity() {
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

bool GameBoard::checkBoard() {
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
bool GameBoard::checkNumOfPlayersBoats(CommonPlayer* A, CommonPlayer* B) {
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

// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
AttackResult GameBoard::play_attack(std::pair<int, int> attack, int attacker, bool* selfHit) {
	if (attack.first == -1 || attack.second == -1) {
		return AttackResult::Miss;
	}
	int x = attack.first - 1;
	int y = attack.second - 1;
	AttackResult result = matrix[x][y]->attack(attacker, selfHit);
	return result;
}


char** GameBoard::getPlayerABoard() {
	return this->playerABoard;
}
char** GameBoard::getPlayerBBoard() {
	return this->playerBBoard;
}
