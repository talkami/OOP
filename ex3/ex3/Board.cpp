#include "Board.h"
#include <boost/algorithm/string.hpp>    
//check out if the lib is ok


Board::Board (){
    this->depth = 0;
    this->rows =0;
    this->col = 0;

} 

~Board::Board(){

}

bool Board::initBoard(const std::string& path) {
	
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
bool Board::loadBoard(const std::string& boardFile) {
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
				this->col = atoi(buffer.substr(0, position));
			}
			catch(std::invalid_argument&))
			{
				return false
			}
		}
		else if (parameter == 1){
			try
			{
				this->row = atoi(buffer.substr(0, position));
			}
			catch(std::invalid_argument&))
			{
				return false
			}
		}
		else if (parameter == 2){
			try
			{
				this->depth = atoi(buffer.substr(0, position));
			}
			catch(std::invalid_argument&))
			{
				return false
			}
		}
		buffer.erase(0, position + delimiter.length());
		parameter ++;
	}
	//init boards fields
	 vector<vector<vector<char>>> board(this->col, vector<char>(this->row), vector<vector<char>>(this->depth));
	 this-> board = board;

	 //is it ok?
	 this->playerABoard = new PlayerBoard(this->row, this->col, this->depth, board, 0);
	 this->playerBBoard = new PlayerBoard(this->row, this->col, this->depth, board, 1);


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
				//setPoint(i, j);
				addToPlayerBoard(currChar, i, j, A, B);
			}
		}
	}
	//check this part
	checkBoatValidity();
	result = checkBoard();
	if (this->hasAdjacentBoats) {
		result = false;
		std::cout << "Adjacent Ships on Board" << std::endl;
	}

	return result;
}





//checking the char read from the file and putting the boat on the board
void Board::addToPlayerBoard(char currentChar, int row, int col, int depth) {

	if (currentChar == 'B') {
		addBoatToBoard(row, col, depth 1, 0);
		this->playerABoard->editBoardAtPoint(row, col, depth,'B');
		this->board.at(depth).at(row).at(col) = 'B';
	}
	else if (currentChar == 'b') {
		addBoatToBoard(this->matrix[row][col], 1, 1, B, A);
		this->playerBBoard.this->editBoardAtPoint(row, col, depth,'b');
		this->board.at(depth).at(row).at(col) = 'b';

	}
	else if (currentChar == 'P') {
		addBoatToBoard(this->matrix[row][col], 2, 0, A, B);
		this->playerABoard.this->editBoardAtPoint(row, col, depth, 'P');
		this->board.at(depth).at(row).at(col) = 'P';
	}
	else if (currentChar == 'p') {
		addBoatToBoard(this->matrix[row][col], 2, 1, B, A);
		this->playerBBoard.this->editBoardAtPoint(row, col, depth,'p');
		this->board.at(depth).at(row).at(col) = 'p';
	}
	else if (currentChar == 'M') {
		addBoatToBoard(this->matrix[row][col], 3, 0, A, B);
		this->playerABoardthis->editBoardAtPoint(row, col, depth,'M');
		this->board.at(depth).at(row).at(col) = 'M';
	}
	else if (currentChar == 'm') {
		addBoatToBoard(this->matrix[row][col], 3, 1, B, A);
		this->playerBBoard->editBoardAtPoint(row, col, depth,'m');
		this->board.at(depth).at(row).at(col) = 'm';
	}
	else if (currentChar == 'D') {
		addBoatToBoard(this->matrix[row][col], 4, 0, A, B);
		this->playerABoard->editBoardAtPoint(row, col, depth,'D');
		this->board.at(depth).at(row).at(col) = 'D';
	}
	else if (currentChar == 'd') {
		addBoatToBoard(this->matrix[row][col], 4, 1, B, A);
		this->playerBBoard->editBoardAtPoint(row, col, depth,'d');
		this->board.at(depth).at(row).at(col) = 'd';
	}
}

void Board::addBoatToBoard(int row, int col, int depth, int size, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard) {
	if (thereIsBoatNearby(row, col, depth)) {
		//there is no boat adjacent to current 
		Coordinate* firstPoint = new Coordinate (row , col, depth);
		Boat* boat = new Boat(size, player, ownerBoard, rivelBoard, firstPoint);
		ownerBoard->addBoat(boat);
	}
	else {
		//there is a boat adjacent to current point
		if (row > 0) {
			char upCoordinateChar = this->board.at(depth).at(row-1).at(col);
			if (upCoordinateChar != ' ') {
				Boat* boat = ownerBoard->getBoatAt (row-1, col, depth);
				//there is a boat above current point 
				checkAdjacentBoat(boat, row , col, depth, size, 1, player, ownerBoard, rivelBoard);
			}
		}

		if (col > 0) {
			char leftCoordinateChar = this->board.at(depth).at(row).at(col-1);
			if (leftCoordinateChar != ' ') {
				Boat* boat = ownerBoard->getBoatAt (row, col-1, depth);
				//there is a boat left of current point
				checkAdjacentBoat(boat, row , col, depth, size, 2, player, ownerBoard, rivelBoard);
			}
		}

		if (depth > 0) {
			char behindCoordinateChar = this->board.at(depth-1).at(row).at(col);
			if (behindCoordinateChar != ' ') {
				//there is a boat left of current point
				Boat* boat = ownerBoard->getBoatAt (row, col, depth-1);
				checkAdjacentBoat(boat, row , col, depth, size, 3, player, ownerBoard, rivelBoard);
			}
		}
	}
}
bool Board:: thereIsBoatNearby(int row, int col, int depth){
	bool boatNearby = false;
	if (depth > 0){
		if (this->board.at(depth-1).at(row).at(col) != ' '){
			boatNearby = true;
		}
	}
	if (row > 0){
		if (this->board.at(depth).at(row-1).at(col) != ' '){
			boatNearby = true;
		}
	}
	if (col > 0){
		if (this->board.at(depth).at(row).at(col-1) != ' '){
			boatNearby = true;
		}
	}
	return boatNearby;
}


void Board::checkAdjacentBoat(Boat* boat, int row, int col, int depth, int size, int direction, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard) {
	if (boat->getBoatSize() == size && boat->getPlayer() == player) {
		if (boat->getDirection() == 0) {
			boat->setDirection(direction);
		}
		//same boat, merge needed
		if (ownerBoard->getBoatAt(row , col, depth) != nullptr) {
			//there is already a boat at point
			if (ownerBoard->getBoatAt(row , col, depth) != boat) {
				mergeBoats(boat, ownerBoard->getBoatAt(row , col, depth), direction);
			}
		}
		else {
			//the is no boat at point
			if (direction != boat->getDirection()) {
				boat->setValidity(false);
			}
			boat->addPoint(row , col, depth);
		}
	}
	else {
		//different boat
		if (ownerBoard->getBoatAt(row , col, depth) == nullptr) {
			Coordinate* firstPoint = new Coordinate (row , col, depth);
			Boat* newBoat = new Boat(size, player, ownerBoard, rivelBoard, firstPoint);
		}
		this->hasAdjacentBoats = true;
	}
}

//checking that all boats are of correct size and shape
void Board::checkBoatValidity() {
	for(int dep =0 ; dep< this->depth; dep++ ){
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->col; j++) {
				
				Boat* boat = nullptr;
				if (this->playerABoard->getBoatAt(row, col, depth) != nullptr){
					boat = this->playerABoard->getBoatAt(row, col, depth) != nullptr;
				}
				else if (this->playerBBoard->getBoatAt(row, col, depth) != nullptr){
					boat = this->playerBBoard->getBoatAt(row, col, depth) != nullptr;
				}

				if (boat != nullptr) {
					if ((boat->getBoatSize() != boat->getAcctualSize()) || !boat->isValid()) {
						int errorNum = (boat->getBoatSize() - 1) + (4 * boat->getPlayer());
						errorArray[errorNum] = true;
						if (boat->getPlayer() == 0) {
							this->playerABoard->removeBoat(boat);
						}
						else if (boat->getPlayer() == 1) {
							this->playerBBoard->removeBoat(boat);
						}
						delete boat;
					}
			}
		}
	}
}


void Board::mergeBoats(Boat* boat1, Boat* boat2, int direction, PlayerBoard* ownerBoard) {

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
	//need to decide where this number is kept
	//merge the boats
	boat1->mergeBoats(boat2);
//	if (boat1->getPlayer() == 0) {
	//	PlayerANumOfBoats--;
	//}
	//else if (boat1->getPlayer() == 1) {
		//PlayerBNumOfBoats--;
	//}
}

bool Board::checkBoard() {
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


PlayerBoard* Board:: getPlayerBoard (int player){
	if(player == 0){
		return this->PlayerABoard;
	}
	else if (player==1){
		return this->PlayerBBoard;
	}
	else{
		return nullptr;
	}
}

