#include "Board.h"
#include <boost/algorithm/string.hpp>    


Board::Board (){
    this.depth = 0;
    this.rows =0;
    this.col = 0;

} 

~Board::Board(){

}

bool GameBoard::initBoard(const std::string& path) {
	
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
		result = loadBoard(boardFileLister.getFilesList()[0]);
	}
	return result;
}


//load GameBoard function
bool GameBoard::loadBoard(const std::string& boardFile) {
	bool result = true;
	setVars();

	std::ifstream fin(boardFile);
	if (!fin) {
		std::cout << "Error reading from file: " << boardFile << std::endl;
		return false;
	}
	//first line holds the number of cos,rows and depth.
	std::string buffer;
	std::getline(fin, buffer);
	//to lower
	boost::algorithm::to_lower(str);
	//get the parameters from the first line
	size_t position = 0;
	int parameter =0;
	while ((position = buffer.find(delimiter)) != std::string::npos) {
		if (parameter == 0){
			try
			{
				this.col = atoi(buffer.substr(0, position));
			}
			catch(std::invalid_argument&))
			{
				return false
			}
		}
		else if (parameter == 1){
			try
			{
				this.row = atoi(buffer.substr(0, position));
			}
			catch(std::invalid_argument&))
			{
				return false
			}
		}
		else if (parameter == 2){
			try
			{
				this.depth = atoi(buffer.substr(0, position));
			}
			catch(std::invalid_argument&))
			{
				return false
			}
		}
		buffer.erase(0, position + delimiter.length());
		parameter ++;
	}
	
	// for depth of the Board
	for(int dep =0 ; dep< this->depth; dep++ ){
	// ignore 1 space line
		std::getline(fin, buffer);

		for (int i = 0; i < this->row; i++) {
			std::getline(fin, buffer);
			for (int j = 0; j < this->col; j++) {
				char currChar = ' ';
				if (j < buffer.length()) {
					currChar = buffer.at(j);
				}
				setPoint(i, j);
				addToPlayerBoard(currChar, i, j, A, B);
			}
		}
	}

	checkBoatValidity();
	result = checkBoard();
	result = (checkNumOfPlayersBoats(A, B) && result);

	if (this->hasAdjacentBoats) {
		result = false;
		std::cout << "Adjacent Ships on Board" << std::endl;
	}

	return result;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			this->matrix[i][j] = new Point(i, j);
		}
	}
}

void Board::addBoatToBoard(Point* point, int size, int player, IBattleshipGameAlgo* owner, IBattleshipGameAlgo* rival) {
	if (!point->getNear()) {
		//there is no boat adjacent to current point
		Boat* boat = new Boat(size, player, owner, rival, point);
		point->setBoat(boat);
		if (player == 0){
			this->PlayerANumOfBoats++;
		}
		else{
			this->PlayerBNumOfBoats++;
		}
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

void Board::checkAdjacentBoat(Boat* boat, Point* point, int size, int direction, int player, IBattleshipGameAlgo* owner, IBattleshipGameAlgo* rival) {
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
			if (direction != boat->getDirection()) {
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
	if (boat1->getPlayer() == 0) {
		PlayerANumOfBoats--;
	}
	else if (boat1->getPlayer() == 1) {
		PlayerBNumOfBoats--;
	}
}