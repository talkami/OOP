#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>

//empty constructor
Board::Board() {
	std::cout << "in Board constructor, about to create a new board." << std::endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			this->matrix[i][j] = new Point;
			this->matrix[i][j]->setX(i);
			this->matrix[i][j]->setY(j);
		}
	}
}

Board::~Board() {
	std::cout << "in Board destructor, about to delete a board." << std::endl;
}

//unused constructor
//Board(const string& boardFile){
//matrix(NULL);
//getBoard(boardFile);
//}


//load board function
void Board::loadBoard(const std::string& boardFile, Player* A, Player* B) {

	/// there is so much shit need to be chekced here!!
	std::string board[10];
	std::ifstream fin(boardFile);
	if (!fin) {
		//error
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (!std::getline(fin, board[i])) {
			board[i] = "          ";
		}
		while (board[i].length < 10) {
			board[i].append(" ");
		}
	}

	// putting up the points- checking if the left/ up to the current point have a boat in it, and by that updating the "NEAR" variable
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			char currentChar = board[i].at(j);
			if (currentChar != ' ' && currentChar != 'b'&& currentChar != 'B'&& currentChar != 'p'&& currentChar != 'P'&& currentChar != 'm'&& currentChar != 'M'&& currentChar != 'd'&& currentChar != 'D') {
				currentChar = ' ';
			}

			if (i>0) {
				this->matrix[i][j]->setLeft(this->matrix[i - 1][j]);
				this->matrix[i - 1][j]->setRight(this->matrix[i][j]);
				if (this->matrix[i - 1][j]->getBoat() != nullptr) {
					this->matrix[i][j]->setNear(true);
				}
			}
			if (j>0) {
				this->matrix[i][j]->setDown(this->matrix[i][j - 1]);
				this->matrix[i][j - 1]->setUp(this->matrix[i][j]);
				if (this->matrix[i][j - 1]->getBoat() != nullptr) {
					this->matrix[i][j]->setNear(true);
				}
			}

			//checking the charecter read from the file and putting the boats on the board - checking there is no boat near boat, and no boat is bigger then it's size and there is no unfamiliar chareter

			if (currentChar == 'b') {
				setBoardsToPoint(this->matrix[i][j], i, j, 1, 0, A, B);
				this->playerABoard[i][j] = 'b';
				this->playerBBoard[i][j] = ' ';
			}
			if (currentChar == 'B') {
				setBoardsToPoint(this->matrix[i][j], i, j, 1, 1, A, B);
				this->playerABoard[i][j] = ' ';
				this->playerBBoard[i][j] = 'B';
			}
			if (currentChar == 'p') {
				setBoardsToPoint(this->matrix[i][j], i, j, 2, 0, A, B);
				this->playerABoard[i][j] = 'p';
				this->playerBBoard[i][j] = ' ';
			}
			if (currentChar == 'P') {
				setBoardsToPoint(this->matrix[i][j], i, j, 2, 1, A, B);
				this->playerABoard[i][j] = ' ';
				this->playerBBoard[i][j] = 'P';
			}
			if (currentChar == 'm') {
				setBoardsToPoint(this->matrix[i][j], i, j, 3, 0, A, B);
				this->playerABoard[i][j] = 'm';
				this->playerBBoard[i][j] = ' ';
			}
			if (currentChar == 'M') {
				setBoardsToPoint(this->matrix[i][j], i, j, 3, 1, A, B);
				this->playerABoard[i][j] = ' ';
				this->playerBBoard[i][j] = 'M';
			}
			if (currentChar == 'd') {
				setBoardsToPoint(this->matrix[i][j], i, j, 4, 0, A, B);
				this->playerABoard[i][j] = 'd';
				this->playerBBoard[i][j] = ' ';
			}
			if (currentChar == 'D') {
				setBoardsToPoint(this->matrix[i][j], i, j, 4, 1, A, B);
				this->playerABoard[i][j] = ' ';
				this->playerBBoard[i][j] = 'D';
			}
			if (currentChar == ' ') {
				this->playerABoard[i][j] = ' ';
				this->playerBBoard[i][j] = ' ';
			}

		}
	}

	//checking there is no boat smaller then it's size and no unValid boats
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Boat* boat = this->matrix[i][j]->getBoat();
			if (boat != nullptr) {
				if (boat->getBoatSize() > boat->getAcctualSize()) { // and no unvalid boats
					errorArray[boat->getPlayer()] = true;
					boat->getOwner()->removeBoat();
					//boat->deleteBoat
					//maybe destroy the boat..
				}
			}
		}
	}
	//checking each player have the right amount of boats
	int numOfBoatsA = A->getNumOfBoats();
	if (numOfBoatsA < 5) {
		errorArray[3] = true;
	}
	if (numOfBoatsA > 5) {
		errorArray[2] = true;
	}
	int numOfBoatsB = B->getNumOfBoats();
	if (numOfBoatsB < 5) {
		errorArray[4] = true;
	}
	if (numOfBoatsB > 5) {
		errorArray[5] = true;
	}

}

// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
// maybe will print out the attack- ask Tal- remember remember!!!!!!!!!!!!!!!
AttackResult Board::play_attack(std::pair<int, int> attack) {
	int x = attack.first;
	int y = attack.second;
	AttackResult result = matrix[x][y]->attack();
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
void Board::setBoardsToPoint(Point* point, int i, int j, int size, int player, Player* A, Player* B) {
	//if no boat near the current point
	if (!point->getNear()) {
		if (player == 0) {
			Boat boat = Boat(size, player, A, B, point);
			point->setBoat(&boat);
		}
		else {
			Boat boat = Boat(size, player, B, A, point);
			point->setBoat(&boat);
		}
		if (i > 0) {
			point->getLeft()->setNear(true);
		}
		if (j > 0) {
			point->getUp()->setNear(true);
		}
	}
	//if there is boat near the current point
	else {
		if (i > 0) {
			Boat* boat = point->getLeft()->getBoat();
			if (boat != nullptr) {
				//if there is a boat left to the current point
				if (boat->getBoatSize() == size && boat->getHorizontal() < 2 && boat->getAcctualSize() < size && boat->getPlayer() == player) {
					//if the left boat match to the current boat variables (size, player, horizontal and it is no bigger then its max size)
					boat->addPoint(point);
					boat->setHorizontal(1);
					if (j > 0) {
						point->getUp()->setNear(true);
					}
				}
				else {
					//if boat is next to another boat - create new boat. do not set the boats unvalid- will be count at the total boat count
					if (boat->getBoatSize() != size || boat->getPlayer() != player) {

						if (player == 0) {
							Boat newBoat = Boat(size, player, A, B, point);
							point->setBoat(&newBoat);
						}
						else {
							Boat newBoat = Boat(size, player, B, A, point);
							point->setBoat(&newBoat);
						}

						point->getLeft->setNear(1);

						if (j > 0) {
							point->getUp->setNear(1);
						}
						this->errorArray[6] = true;
					}
					//if the boat is at wrong shape or too big set the boat unvalid- won't be count at the total boat count
					else {
						boat->setValid(false);
						point->setBoat(boat);
						if (i > 0) {
							point->getLeft()->setNear(1);
						}
						if (j > 0) {
							point->getUp()->setNear(1);
						}
						this->errorArray[player] = true;
					}
				}
			}
		}
		if (j > 0) {
			Boat* boat = point->getUp()->getBoat();
			if (boat != nullptr) {
				//if there is a boat above  the current point
				if (boat->getBoatSize() == size && boat->getHorizontal() != 1 && boat->getAcctualSize() < size && boat->getPlayer() == player) {
					//if the  boat above match to the current boat variables (size, player, horizontal and it is no bigger then its max size)
					boat->addPoint(point);
					boat->setHorizontal(2);
					if (i > 0) {
						point->getLeft()->setNear(1);
					}
				}
				else {
					if (boat->getBoatSize() != size || boat->getPlayer() != player) {
						//if boat is next to another boat - create new boat. do not set the boats unvalid- will be count at the total boat count
						if (point->getBoat() != nullptr) {
							this->errorArray[6] = true;
							return;
						}
						if (player == 0) {
							Boat newBoat = Boat(size, player, A, B, point);
							point->setBoat(&newBoat);
						}
						else {
							Boat newBoat = Boat(size, player, B, A, point);
							point->setBoat(&newBoat);
						}

						point->getLeft()->setNear(1);

						if (j > 0) {
							point->getUp()->setNear(1);
						}
						this->errorArray[6] = true;
						return;
					}
					else {
						//if the boat is at wrong shape or too big set the boat unvalid- won't be count at the total boat count
						boat->setValid(false);
						point->setBoat(boat);
						if (i > 0) {
							point->getLeft()->setNear(true);
						}
						if (j > 0) {
							point->getUp()->setNear(true);
						}
						this->errorArray[player] = true;
						return;
					}
				}
			}
		}

	}
}