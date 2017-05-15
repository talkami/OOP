#include "Board.h"

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
			this->matrix[i][j] = new Point(i,j);
		}
	}
}

void Board::addBoatToBoard(Point* point, int size, int player, CommonPlayer* owner, CommonPlayer* rival) {
	if (!point->getNear()) {
		//there is no boat adjacent to current point
		Boat* boat = new Boat(size, player, owner, rival, point);
		point->setBoat(boat);
	}
	else {
		//there is a boat adjacent to current point
		if (point->getRow() > 0) {
			Boat* boat = point->getUp()->getBoat();
			if (boat != nullptr) {
				//there is a boat above current point 
				checkAdjacentBoat(boat, point, size, 1, player, owner, rival);
			}
		}

		if (point->getCol() > 0) {
			Boat* boat = point->getLeft()->getBoat();
			if (boat != nullptr) {
				//there is a boat left of current point
				checkAdjacentBoat(boat, point, size, 2, player, owner, rival);
			}
		}
	}
}

void Board::checkAdjacentBoat(Boat* boat, Point* point, int size, int direction, int player, CommonPlayer* owner, CommonPlayer* rival) {
	if (boat->getBoatSize() == size && boat->getPlayer() == player) {
		if (boat->getDirection() == 0) {
			boat->setDirection(direction);
		}
		//same boat, merge needed
		if (point->getBoat() != nullptr) {
			//there is already a boat at point
			if (point->getBoat() != boat) {
				mergeBoats(boat, point->getBoat(), direction);
			}
		}
		else {
			//the is no boat at point
			if (direction != boat->getDirection()){
				boat->setValidity(false);
			}
			boat->addPoint(point);
			point->setBoat(boat);
		}
	}
	else {
		//different boat
		if (point->getBoat() == nullptr) {
			Boat* newBoat = new Boat(size, player, owner, rival, point);
			point->setBoat(newBoat);
		}			
		this->hasAdjacentBoats = true;
	}
}

void Board::mergeBoats(Boat* boat1, Boat* boat2, int direction) {

	//make sure boat1 is bigger (we will later 'copy' boat2 onto boat1, this makes the process 'easier') 
	if (boat2->getAcctualSize() > boat1->getAcctualSize()) {
		Boat *tmp = boat2;
		boat2 = boat1;
		boat1 = tmp;
	}

	//check if merge will result in an invalid boat
	if (boat2->getDirection() == 0) {
		if (boat1->getDirection() != direction) {
			boat1->setValidity(false);
		}
	}
	else if (boat1->getDirection() != boat2->getDirection()) {
		boat1->setValidity(false);
	}

	//merge the boats
	boat1->mergeBoats(boat2);
}