#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>

//empty constructor
Board::Board() :
	matrix(NULL) {}


//unused constructor
//Board(const string& boardFile){
//matrix(NULL);
//getBoard(boardFile);
//}


//load board function
void Board::loadBoard(const string& boardFile, Player A, Player B) {

	/// there is so much shit need to be chekced here!!
	string board[10];
	ifstream fin(boardFile);
	for (int i = 0; i < 10; i++) {
		std::getline(fin, board[i]);
	}

	// putting up the points- checking if the left/ up to the current point have a boat in it, and by that updating the "NEAR" variable
	Point points_matrix[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << board[i].at(i);
			points_matrix[i][j].setX(i);
			points_matrix[i][j].setY(j);
			if (i>0) {
				points_matrix[i][j].setLeft(&points_matrix[i - 1][j]);
				points_matrix[i - 1][j].setRight(&points_matrix[i][j]);
				if (points_matrix[i - 1][j].getBoat != NULL) {
					points_matrix[i][j].setNear(1);
				}
			}
			if (j>0) {
				points_matrix[i][j].setDown(&points_matrix[i][j - 1]);
				points_matrix[i][j - 1].setUp(&points_matrix[i][j]);
				if (points_matrix[i][j - 1].getBoat != NULL) {
					points_matrix[i][j].setNear(1);
				}
			}

			//checking the charecter read from the file and putting the boats on the board - checking there is no boat near boat, and no boat is bigger then it's size and there is no unfamiliar chareter
			int error = 0;
			if (cout == 'b') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 1, 0);
			}
			if (cout == 'B') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 1, 1);
			}
			if (cout == 'p') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 2, 0);
			}
			if (cout == 'P') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 2, 1);
			}
			if (cout == 'm') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 3, 0);
			}
			if (cout == 'M') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 3, 1);
			}
			if (cout == 'd') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 4, 0);
			}
			if (cout == 'D') {
				error = setBoardsToPoint(&points_matrix[i][j], i, j, 4, 1);
			}
			if (cout != ' ' && cout != 'b'&& cout != 'B'&& cout != 'p'&& cout != 'P'&& cout != 'm'&& cout != 'M'&& cout != 'd'&& cout != 'D') {
				error = -1;
			}
		}
	}

	//checking each player have the right amount of boats
	// ask Tal!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! remember remember


	//checking there is no boat smaller then it's size
	int boatSmallerThenSize = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Boat boat = points_matrix[i][j].getBoat();
			if (boat != NULL) {
				if (boat.getSize() > boat.getPointNum()) {
					boatSmallerThenSize = -1;
				}
			}
		}
	}
	this.matrix = points_matrix[10][10];
}

// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
// maybe will print out the attack- ask Tal- remember remember!!!!!!!!!!!!!!!
AttackResult Board::play_attack(pair<int, int>) {
	int x = pair.first; //????
	int y = pair.second; // ????????????
	AttackResult result = matrix[x][y].attack();
	return result;
	// print the attack result?
}



//inner function helping the loadBoard. pretty much useless outside.
int Board::setBoardsToPoint(Point* point, int i, int j, int size, int player, Player A, Player B) {
	if (point->getNear == 0) {
		if (player == 0) {
			Boat boat = Boat(size, player, &A);
		}
		else {
			Boat boat = Boat(size, player, &B);
		}
		point->setBoat(boat);
		if (i > 0) {
			point->getLeft->setNear(1);
		}
		if (j > 0) {
			point->getUp->setNear(1);
		}
	}
	else {
		if (size > 1) {
			if (i > 0) {
				Boat boat = point->getLeft->getBoat();
				if (boat != NULL) {
					if (boat.getSize() == size && boat.getHorizontal() < 2 && boat.getPointsNum() < size && boat.getPlayer() == player{
						boat.AddPoint();
					boat.setHorizontal(1);
					if (j > 0) {
						point->getUp->setNear(1);
					}
					}
					else {
						//error
						return -1;
					}
				}
			}
			if (j > 0) {
				Boat boat = point->getUp->getBoat();
				if (boat != NULL) {
					if (boat.getSize() == size && boat.getHorizontal() != 1 && boat.getPointsNum() < size && boat.getPlayer() == player{
						boat.AddPoint();
					boat.setHorizontal(2);
					if (i > 0) {
						point->getLeft->setNear(1);
					}
					}
					else {
						//error
						return -1;
					}
				}
			}
		}
	}
}
