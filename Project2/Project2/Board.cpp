#include "Board.h"
#include <string>
#include <fstream>
#include <iostream>


//empty constructor
Board::Board() {

}

bool Board ::playerLoadBoard (char** playerBoard, Player* player, int rows, int cols){
	setVars (rows,cols);
	createBoard (playerBoard, player, nullptr,  rows,  cols);
}
Board::~Board() {
	for (int i = 0; i<this->rows; i++) {
		delete[]this->playerABoard[i];
		delete[]this->playerBBoard[i];
	}
	delete[]playerABoard;
	delete[]playerBBoard;
}

//unused constructor
//Board(const string& boardFile){
//matrix(NULL);
//getBoard(boardFile);
//}

void Board ::setVars ( int rows, int cols){
	this-> rows = rows;
	this-> cols = cols;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->matrix[i][j] = new Point;
			this->matrix[i][j]->setX(i);
			this->matrix[i][j]->setY(j);
		}
	}
	this->playerABoard = new char *[rows];
	this->playerBBoard = new char *[rows];
	for (int i = 0; i < rows; i++) {
		this->playerABoard[i] = new char[cols];
		this->playerBBoard[i] = new char[cols];
	}
}



//load board function
bool Board::loadBoard(const std::string& boardFile, Player* A, Player* B, int rows, int cols) {
	bool result = true;

	/// there is so much shit need to be chekced here!!
	std::string board[rows];
	std::ifstream fin(boardFile);
	if (!fin) {
		//error
		return false;
	}
	for (int i = 0; i < rows; i++) {
		if (!std::getline(fin, board[i])) {
			board[i] = "          ";
		}
		while (board[i].length() < cols) {
			board[i].append(" ");
		}
	}
	setVars (rows, cols);
	result = createBoard (board, A, B, rows, cols);
	return result;
}
bool Board::createBoard (char** board, Player* A, Player* B, int rows, int cols){
	// putting up the points- checking if the left/ up to the current point have a boat in it, and by that updating the "NEAR" variable
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			char currentChar = board[i].at(j);

			if (i>0) {
				this->matrix[i][j]->setUp(this->matrix[i - 1][j]);
				this->matrix[i - 1][j]->setDown(this->matrix[i][j]);
				if (this->matrix[i - 1][j]->getBoat() != nullptr) {
					this->matrix[i][j]->setNear(true);
				}
			}
			if (j>0) {
				this->matrix[i][j]->setLeft(this->matrix[i][j - 1]);
				this->matrix[i][j - 1]->setRight(this->matrix[i][j]);
				if (this->matrix[i][j - 1]->getBoat() != nullptr) {
					this->matrix[i][j]->setNear(true);
				}
			}
			addToPlayerBoard(currentChar, i, j, A, B);
		}
	}
	checkBoatValidity();

	result = checkBoard();
	
	result = (checkNumOfPlayersBoats(A,B) && result);

	if (this->errorArray[8]) {
		result = false;
		std::cout << "Adjacent Ships on Board" << std::endl;
	}
	return result;
	}

//checking the charecter read from the file and putting the boats on the board
void Board::addToPlayerBoard(char currentChar, int row, int col, Player* A, Player* B) {
	
	if (currentChar == 'B') {
		if (A != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 1, 0, A, B);
			this->playerABoard[row][col] = 'B';
			this->playerBBoard[row][col] = ' ';
		}

	}
	if (currentChar == 'b') {
		if (B != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 1, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'b';
		}
	}
	if (currentChar == 'P') {
		if (A != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 2, 0, A, B);
			this->playerABoard[row][col] = 'P';
			this->playerBBoard[row][col] = ' ';
		}
	}
	if (currentChar == 'p') {
		if (B != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 2, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'p';
		}
	}
	if (currentChar == 'M') {
		if (A != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 3, 0, A, B);
			this->playerABoard[row][col] = 'M';
			this->playerBBoard[row][col] = ' ';
		}
	}
	if (currentChar == 'm') {
		if (B != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 3, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'm';
		}
	}
	if (currentChar == 'D') {
		if (A != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 4, 0, A, B);
			this->playerABoard[row][col] = 'D';
			this->playerBBoard[row][col] = ' ';
		}
	}
	if (currentChar == 'd') {
		if (B != nullptr){
			addBoatToBoard(this->matrix[row][col], row, col, 4, 1, B, A);
			this->playerABoard[row][col] = ' ';
			this->playerBBoard[row][col] = 'd';
		}
	}
	else {
		this->playerABoard[row][col] = ' ';
		this->playerBBoard[row][col] = ' ';
	}
}

//checking that all boats are of correct size and shape
void Board::checkBoatValidity() {	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Boat* boat = this->matrix[i][j]->getBoat();
			if (boat != nullptr) {
				if ((boat->getBoatSize() != boat->getAcctualSize()) || !boat->isValid()) {
					int errorNum = (boat->getBoatSize() - 1) + (4 * boat->getPlayer());
					errorArray[errorNum] = true;
					if (boat->getRival != nullptr){
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

	if (errorArray[0]){
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
bool Board::checkNumOfPlayersBoats(Player* A, Player* B) {
	bool result = true;
	if (A != nullptr){
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
	if (B != nullptr){
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


bool Board :: updateBoardAfterAttack (Point * point, AttackResult result){
	if 
}


// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
// maybe will print out the attack- ask Tal- remember remember!!!!!!!!!!!!!!!
AttackResult Board::play_attack(std::pair<int, int> attack, int attacker, bool* selfHit) {
	int x = attack.first -1;
	int y = attack.second -1;
	AttackResult result = matrix[x][y]->attack(attacker, selfHit);
	return result;
	// print the attack result?
}

char** Board::getPlayerABoard() {
	return this->playerABoard;
}
char** Board::getPlayerBBoard() {
	return this->playerBBoard;
}

//inner function helping the loadBoard. pretty much useless outside.
void Board::addBoatToBoard(Point* point, int i, int j, int size, int player, Player* owner, Player* rival) {
	//if no boat near the current point
	point->invalidToAttack();
	if (!point->getNear()) {
		Boat* boat =new Boat(size, player, owner, rival, point);
		point->setBoat(boat);

		if (i > 0) {
			point->getUp()->setNear(true);
			point->getUp()->invalidToAttack();
		}
		if (j > 0) {
			point->getLeft()->setNear(true);
			point->getLeft->invalidToAttack();
		}
	}
	//if there is boat near the current point
	else {
		if (i > 0) {
			Boat* boat = point->getUp()->getBoat();
			if (boat != nullptr) {
				//if there is a boat left to the current point
				if (boat->getBoatSize() == size && boat->getHorizontal() < 2 && boat->getAcctualSize() < size && boat->getPlayer() == player) {
					//if the left boat match to the current boat variables (size, player, horizontal and it is no bigger then its max size)

					boat->addPoint(point);
					boat->setHorizontal(1);
					point->setBoat(boat);
					point->getUp()->setNear(true);
					point->getUp()->invalidToAttack();
					if (j > 0) {
						point->getLeft()->setNear(true);
						point->getLeft->invalidToAttack();
					}
				}
				else {
					//if boat is next to another boat - create new boat. do not set the boats unvalid- will be count at the total boat count
					if (boat->getBoatSize() != size || boat->getPlayer() != player) {
						Boat* newBoat = new Boat(size, player, owner, rival, point);
						point->setBoat(newBoat);
						if (j > 0) {
							point->getLeft()->setNear(true);
							point->getLeft->invalidToAttack();

						}
						this->errorArray[8] = true;
					}
					//if the boat is at wrong shape or too big set the boat unvalid- won't be count at the total boat count
					else {
						boat->addPoint(point);
						boat->setValid(false);
						
						point->setBoat(boat);
						point->getUp()->setNear(true);
						point->getUp()->invalidToAttack();
						if (j > 0) {
							point->getLeft()->setNear(true);
							point->getLeft->invalidToAttack();
						}
					}
				}
			}
		}
		if (j > 0) {
			Boat* boat = point->getLeft()->getBoat();

			if (boat != nullptr) {
				//if there is a boat next to the current point
				if (boat->getBoatSize() == size && boat->getHorizontal() != 1 && boat->getAcctualSize() < size && boat->getPlayer() == player) {
					//if the  boat above match to the current boat variables (size, player, horizontal and it is no bigger then its max size)
					boat->addPoint(point);
					boat->setHorizontal(2);
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
					if (i > 0) {
						point->getUp()->setNear(true);
					}
				}
				else {
					if (boat->getBoatSize() != size || boat->getPlayer() != player) {
						//if boat is next to another boat - create new boat. do not set the boats unvalid- will be count at the total boat count
						if (point->getBoat() != nullptr) {
							this->errorArray[8] = true;
							return;
						}
						Boat* newBoat = new Boat(size, player, owner, rival, point);
						point->setBoat(newBoat);

						point->getLeft()->setNear(true);

						if (i > 0) {
							point->getUp()->setNear(true);
						}
						this->errorArray[8] = true;
						return;
					}
					else {
						//if the boat is at wrong shape or too big set the boat invalid- won't be count at the total boat count
						if ((point->getBoat() != nullptr) && (point->getBoat() != boat)) {
							delete point->getBoat();
							owner->removeBoat();
						}
						boat->setValid(false);
						boat->addPoint(point);

						point->setBoat(boat);
						if (i > 0) {
							point->getUp()->setNear(true);
						}
						
						point->getLeft()->setNear(true);

						return;
					}
				}
			}
		}

	}
}

void Board::setInvalidAttack(int row, int col){}
bool Board::isValidAttack(int row, int col) { return true; }