#include "Board.h"
#include <algorithm>
#include <string>

#include <iostream>

//load GameBoard function
bool Board::loadBoard(const std::string& boardFile, Logger* logger) {
	bool result = true;
	logger->logMessage("Started Checking " + boardFile);

	std::ifstream fin(boardFile);
	if (!fin) {
		logger->logMessage("Error reading from file: " + boardFile);
		return false;
	}
	//first line holds the number of cols, rows and depth.
	std::string buffer;
	std::getline(fin, buffer);
	if (!setUpParameters(buffer)) {
		logger->logMessage("Invalid board parameter for: " + boardFile);
		return false;
	}

	 this->playerABoard.setVars(this->numOfRows, this->numOfCols, this->depth, 0);
	 this->playerBBoard.setVars(this->numOfRows, this->numOfCols, this->depth, 1);

	 for (int dep = 0; dep < this->depth; dep++) {
	// ignore 1 space line
		std::getline(fin, buffer);

		for (int row = 0; row < this->numOfRows; row++) {
			std::getline(fin, buffer);
			for (int col = 0; col < this->numOfCols; col++) {
				char currChar = ' ';
				if (col < buffer.length()) {
					currChar = buffer.at(col);
				}
				addToPlayerBoard(currChar, Coordinate(row, col, dep));
			}
		}
	}

	checkBoatValidity();
	result = checkBoard(logger);
	if (this->hasAdjacentBoats) {
		result = false;
		logger->logMessage("Adjacent Ships on Board");
	}

	logger->logMessage("Finished Checking " + boardFile);
	return result;
}

bool Board::setUpParameters(std::string params) {
	std::transform(params.begin(), params.end(), params.begin(), ::tolower);
	size_t start = 0;
	size_t end = params.find("x");

	try {
		this->numOfCols = stoi(params.substr(start, end));
		start += end + 1;

		end = params.substr(start).find("x");
		this->numOfRows = stoi(params.substr(start, end));
		start += end + 1;

		end = params.substr(start).find("x");
		this->depth = stoi(params.substr(start, end));
	}
	catch (std::invalid_argument&) {
		return false;
	}
	if (this->numOfCols <= 0 || this->numOfRows <= 0 || this->depth <= 0) {
		return false;
	}

	board.resize(this->depth);
	for (int i = 0; i < depth; i++) {
		board.at(i).resize(this->numOfRows);
		for (int j = 0; j < this->numOfRows; j++) {
			board.at(i).at(j).resize(this->numOfCols);
		}
	}
	return true;
}

//checking the char read from the file and putting the boat on the board
void Board::addToPlayerBoard(char currentChar, Coordinate coor) {

	if (currentChar == 'B') {
		addBoatToBoard(coor, 1, 0);
		this->playerABoard.editBoardAtPoint(coor, 'B');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'B';
	}
	else if (currentChar == 'b') {
		addBoatToBoard(coor, 1, 1);
		this->playerBBoard.editBoardAtPoint(coor, 'b');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'b';
	}
	else if (currentChar == 'P') {
		addBoatToBoard(coor, 2, 0);
		this->playerABoard.editBoardAtPoint(coor, 'P');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'P';
	}
	else if (currentChar == 'p') {
		addBoatToBoard(coor, 2, 1);
		this->playerBBoard.editBoardAtPoint(coor, 'p');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'p';
	}
	else if (currentChar == 'M') {
		addBoatToBoard(coor, 3, 0);
		this->playerABoard.editBoardAtPoint(coor, 'M');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'M';
	}
	else if (currentChar == 'm') {
		addBoatToBoard(coor, 3, 1);
		this->playerBBoard.editBoardAtPoint(coor, 'm');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'm';
	}
	else if (currentChar == 'D') {
		addBoatToBoard(coor, 4, 0);
		this->playerABoard.editBoardAtPoint(coor, 'D');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'D';
	}
	else if (currentChar == 'd') {
		addBoatToBoard(coor, 4, 1);
		this->playerBBoard.editBoardAtPoint(coor, 'd');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'd';
	}
	else {
		this->playerBBoard.editBoardAtPoint(coor, ' ');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = ' ';
	}
}

void Board::addBoatToBoard(Coordinate coor, int size, int player) {
	if (!isThereABoatNearby(coor)) {
		//there is no boat adjacent to current 
		this->boats.emplace_back(std::make_shared<Boat>(size, player, coor));
	}
	else {
		//there is a boat adjacent to current point
		if (coor.depth > 0) {
			char behindCoordinateChar = this->board.at(coor.depth - 1).at(coor.row).at(coor.col);
			if (behindCoordinateChar != ' ') {
				std::shared_ptr<Boat> boat = getBoatAt(Coordinate(coor.row, coor.col, coor.depth - 1));
				checkAdjacentBoat(boat, coor, size, 3, player);
			}
		}

		if (coor.row > 0) {
			char upCoordinateChar = this->board.at(coor.depth).at(coor.row-1).at(coor.col);
			if (upCoordinateChar != ' ') {
				std::shared_ptr<Boat> boat = getBoatAt(Coordinate(coor.row-1, coor.col, coor.depth));
				checkAdjacentBoat(boat, coor, size, 1, player);
			}
		}

		if (coor.col > 0) {
			char leftCoordinateChar = this->board.at(coor.depth).at(coor.row).at(coor.col-1);
			if (leftCoordinateChar != ' ') {
				std::shared_ptr<Boat> boat = getBoatAt(Coordinate(coor.row, coor.col-1, coor.depth));
				checkAdjacentBoat(boat, coor, size, 2, player);
			}
		}
	}
}

bool Board::isThereABoatNearby(Coordinate coor){
	bool boatNearby = false;
	if (coor.depth > 0){
		if (this->board.at(coor.depth-1).at(coor.row).at(coor.col) != ' '){
			boatNearby = true;
		}
	}
	if (coor.row > 0){
		if (this->board.at(coor.depth).at(coor.row-1).at(coor.col) != ' '){
			boatNearby = true;
		}
	}
	if (coor.col > 0){
		if (this->board.at(coor.depth).at(coor.row).at(coor.col-1) != ' '){
			boatNearby = true;
		}
	}
	return boatNearby;
}

std::shared_ptr<Boat> Board::getBoatAt(Coordinate coor) {
	for (std::shared_ptr<Boat> boat : this->boats) {
		if (boat->containsPoint(coor)) {
			return boat;
		}
	}
	return nullptr;
}

void Board::checkAdjacentBoat(std::shared_ptr<Boat> boat, Coordinate coor, int size, int direction, int player) {
	if (boat != nullptr && boat->getBoatSize() == size && boat->getPlayer() == player) {
		if (boat->getDirection() == 0) {
			boat->setDirection(direction);
		}
		//same boat, merge needed
		std::shared_ptr<Boat> otherBoat = getBoatAt(coor);
		if (otherBoat != nullptr) {
			//there is already a boat at point
			if (otherBoat != boat) {
				mergeBoats(boat, otherBoat, direction);
			}
		}
		else {
			//the is no boat at point
			if (direction != boat->getDirection()) {
				boat->setValidity(false);
			}
			boat->addPoint(coor);
		}
	}
	else {
		//different boat
		if (getBoatAt(coor) == nullptr) {
			this->boats.emplace_back(std::make_shared<Boat>(size, player, coor));
		}
		this->hasAdjacentBoats = true;
	}
}

void Board::mergeBoats(std::shared_ptr<Boat> boat1, std::shared_ptr<Boat> boat2, int direction) {

	//make sure boat1 is bigger (we will later 'copy' boat2 onto boat1, this makes the process 'easier') 
	if (boat2->getAcctualSize() > boat1->getAcctualSize()) {
		std::shared_ptr<Boat> tmp = boat2;
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
	deleteBoat(boat2);
}

void Board::deleteBoat(std::shared_ptr<Boat> boat) {
	for (int i = 0; i < this->boats.size(); i++) {
		if (boat->equals(this->boats.at(i))) {
			this->boats.erase(this->boats.begin() + i);
		}
	}
}


//checking that all boats are of correct size and shape
void Board::checkBoatValidity() {
	for (int dep = 0; dep < this->depth; dep++) {
		for (int row = 0; row < this->numOfRows; row++) {
			for (int col = 0; col < this->numOfCols; col++) {

				Coordinate point = Coordinate(row, col, dep);
				std::shared_ptr<Boat> boat = getBoatAt(point);
				if (boat != nullptr) {
					if ((boat->getBoatSize() != boat->getAcctualSize()) || !boat->isValid()) {
						int errorNum = (boat->getBoatSize() - 1) + (4 * boat->getPlayer());
						errorArray[errorNum] = true;
					}
				}
			}
		}
	}
}

bool Board::checkBoard(Logger* logger) {
	bool result = true;

	if (this->errorArray[0]) {
		logger->logMessage("Wrong size or shape for ship B for player A");
		result = false;
	}
	if (this->errorArray[1]) {
		logger->logMessage("Wrong size or shape for ship P for player A");
		result = false;
	}
	if (this->errorArray[2]) {
		logger->logMessage("Wrong size or shape for ship M for player A");
		result = false;
	}
	if (this->errorArray[3]) {
		logger->logMessage("Wrong size or shape for ship D for player A");
		result = false;
	}
	if (this->errorArray[4]) {
		logger->logMessage("Wrong size or shape for ship b for player B");
		result = false;
	}
	if (this->errorArray[5]) {
		logger->logMessage("Wrong size or shape for ship p for player B");
		result = false;
	}
	if (this->errorArray[6]) {
		logger->logMessage("Wrong size or shape for ship m for player B");
		result = false;
	}
	if (this->errorArray[7]) {
		logger->logMessage("Wrong size or shape for ship d for player B");
		result = false;
	}
	return result;
}

BoardData& Board::getPlayerBoard (int player){
	std::cout << "getting board for player " << player << std::endl;
	if(player == 0){
		std::cout << "player 0 board" << std::endl;
		return this->playerABoard;
	}
	else {
		return this->playerBBoard;
	}
}

std::unique_ptr<GameBoard> Board::getGameBoard() {
	return std::make_unique<GameBoard>(this->numOfRows, this->numOfCols, this->depth, this->boats);
}