#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>




//empty constructor
Board::Board(){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			this->matrix[i][j] = new Point;
			this->matrix[i][j]->setX(i);
			this->matrix[i][j]->setY(j);
		}
	}
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
	for (int i = 0; i < 10; i++) {
		std::getline(fin, board[i]);
	}

	// putting up the points- checking if the left/ up to the current point have a boat in it, and by that updating the "NEAR" variable
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			char currentChar = board[i].at(j);
			if (i>0){
				this->matrix[i][j]->setLeft (this->matrix[i - 1][j]);
				this->matrix[i-1][j]->setRight (this->matrix[i][j]);
				if (this->matrix[i-1][j]->getBoat != nullptr){
					this->matrix[i][j]->setNear(true);
				}
			}
			if (j>0){
				this->matrix[i][j]->setDown (this->matrix[i][j-1]);
				this->matrix[i][j-1]->setUp (this->matrix[i][j]);
				if (this->matrix[i][j - 1]->getBoat != nullptr){
					this->matrix[i][j]->setNear(true);
				}
			}
			
			//checking the charecter read from the file and putting the boats on the board - checking there is no boat near boat, and no boat is bigger then it's size and there is no unfamiliar chareter
			int error = 0;
			if (currentChar == 'b'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 1, 0, A, B);
			}
			if (currentChar == 'B'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 1, 1,A,B);
			}
			if (currentChar == 'p'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 2, 0,A,B);
			}
			if (currentChar == 'P'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 2, 1,A,B);
			}
			if (currentChar == 'm'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 3, 0,A,B);
			}
			if (currentChar == 'M'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 3, 1,A,B);
			}
			if (currentChar == 'd'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 4, 0,A,B);
			}
			if (currentChar == 'D'){
				error = setBoardsToPoint(this->matrix[i][j], i, j, 4, 1,A,B);
			}
			if (currentChar != ' ' && currentChar != 'b'&& currentChar != 'B'&& currentChar != 'p'&& currentChar != 'P'&& currentChar != 'm'&& currentChar != 'M'&& currentChar != 'd'&& currentChar != 'D'){
				error = -1;
			}
		}
	}

	//checking each player have the right amount of boats
	// ask Tal!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! remember remember


	//checking there is no boat smaller then it's size
	int boatSmallerThenSize = 0;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			Boat* boat = this->matrix[i][j]->getBoat();
			if ( boat != nullptr){
				if (boat->getBoatSize() > boat->getAcctualSize()){
					boatSmallerThenSize = -1;
				}
			}
		}
	}
}

// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
// maybe will print out the attack- ask Tal- remember remember!!!!!!!!!!!!!!!
	AttackResult Board::play_attack(std::pair<int, int> attack){
		int x = attack.first; 
		int y = attack.second; 
		AttackResult result = matrix[x][y]->attack();
		return result;
		// print the attack result?
	}



	//inner function helping the loadBoard. pretty much useless outside.
	int Board::setBoardsToPoint(Point* point, int i, int j, int size, int player, Player* A, Player* B){
		if (point->getNear == 0){
			if (player == 0){
				Boat boat = Boat(size, player, A, B);
				point->setBoat(&boat);
			}
			else{
				Boat boat = Boat(size, player, B, A);
				point->setBoat(&boat);
			}
			if (i > 0){
				point->getLeft->setNear(1);
			}
			if (j > 0){
				point->getUp->setNear(1);
			}
		}
		else{
			if (size > 1){
				if (i > 0){
					Boat* boat = point->getLeft->getBoat();
					if (boat != nullptr){
						if (boat->getBoatSize() == size && boat->getHorizontal() < 2 && boat->getAcctualSize() < size && boat->getPlayer() == player){
							boat->addPoint();
							boat->setHorizontal(1);
							if (j > 0){
								point->getUp->setNear(1);
							}
						}
						else{
							//error
							return -1;
						}
					}
				}
				if (j > 0){
					Boat* boat = point->getUp->getBoat();
					if (boat != nullptr){
						if (boat->getBoatSize() == size && boat->getHorizontal() != 1 && boat->getAcctualSize() < size && boat->getPlayer() == player){
							boat->addPoint();
							boat->setHorizontal(2);
							if (i > 0){
								point->getLeft->setNear(1);
							}
						}
						else{
							//error
							return -1;
						}
					}
				}
			}
		}
	}
