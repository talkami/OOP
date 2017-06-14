#include "Board.h"
#include <algorithm>
#include <string>

Board::~Board() {
}

//load GameBoard function
bool Board::loadBoard(const std::string& boardFile, Logger* logger) {
	bool result = true;
	this->logger = logger;

	std::ifstream fin(boardFile);
	if (!fin) {
		this->logger->logMessage("Error reading from file: " + boardFile);
		return false;
	}
	//first line holds the number of cols, rows and depth.
	std::string buffer;
	std::getline(fin, buffer);
	if (!setUpParameters(buffer)) {
		this->logger->logMessage("Invalid board parameter for: " + boardFile);
		return false;
	}

	 this->playerABoard =  PlayerBoard(this->numOfRows, this->numOfCols, this->depth, 0);
	 this->playerBBoard = PlayerBoard(this->numOfRows, this->numOfCols, this->depth, 1);

	// for depth of the Board
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
	//check this part
	checkBoatValidity();
	result = checkBoard();
	if (this->hasAdjacentBoats) {
		result = false;
		this->logger->logMessage(boardFile + ": Adjacent Ships on Board" );
	}

	this->logger->logMessage("Finished checking " + boardFile);
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
			board.at(i).at(j).resize(this->numOfCols, ' ');
		}
	}
	return true;
}

//checking the char read from the file and putting the boat on the board
void Board::addToPlayerBoard(char currentChar, Coordinate coor) {

	if (currentChar == 'B') {
		addBoatToBoard(coor, 1, 0, this->playerABoard, this->playerBBoard);
		this->playerABoard->editBoardAtPoint(coor,'B');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'B';
	}
	else if (currentChar == 'b') {
		addBoatToBoard(coor, 1, 1, this->playerBBoard, this->playerABoard);
		this->playerBBoard->editBoardAtPoint(coor,'b');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'b';
	}
	else if (currentChar == 'P') {
		addBoatToBoard(coor, 2, 0, this->playerABoard, this->playerBBoard);
		this->playerABoard->editBoardAtPoint(coor, 'P');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'P';
	}
	else if (currentChar == 'p') {
		addBoatToBoard(coor, 2, 1, this->playerBBoard, this->playerABoard);
		this->playerBBoard->editBoardAtPoint(coor,'p');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'p';
	}
	else if (currentChar == 'M') {
		addBoatToBoard(coor, 3, 0, this->playerABoard, this->playerBBoard);
		this->playerABoard->editBoardAtPoint(coor,'M');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'M';
	}
	else if (currentChar == 'm') {
		addBoatToBoard(coor, 3, 1, this->playerBBoard, this->playerABoard);
		this->playerBBoard->editBoardAtPoint(coor,'m');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'm';
	}
	else if (currentChar == 'D') {
		addBoatToBoard(coor, 4, 0, this->playerABoard, this->playerBBoard);
		this->playerABoard->editBoardAtPoint(coor,'D');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'D';
	}
	else if (currentChar == 'd') {
		addBoatToBoard(coor, 4, 1, this->playerBBoard, this->playerABoard);
		this->playerBBoard->editBoardAtPoint(coor,'d');
		this->board.at(coor.depth).at(coor.row).at(coor.col) = 'd';
	}
}

void Board::addBoatToBoard(Coordinate coor, int size, int player, std::shared_ptr<PlayerBoard> ownerBoard, std::shared_ptr<PlayerBoard> rivalBoard) {
	if (!thereIsABoatNearby(coor)) {
		//there is no boat adjacent to current 
		std::shared_ptr<Boat> boat = std::make_shared<Boat>(size, player, ownerBoard, rivalBoard, coor);
		ownerBoard->addBoat(boat);
	}
	else {
		//there is a boat adjacent to current point
		if (coor.row > 0) {
			char upCoordinateChar = this->board.at(coor.depth).at(coor.row-1).at(coor.col);
			if (upCoordinateChar != ' ') {
				std::shared_ptr<Boat> boat = ownerBoard->getBoatAt(Coordinate(coor.row-1, coor.col, coor.depth));
				checkAdjacentBoat(boat, coor, size, 1, player, ownerBoard, rivalBoard);
			}
		}

		if (coor.col > 0) {
			char leftCoordinateChar = this->board.at(coor.depth).at(coor.row).at(coor.col-1);
			if (leftCoordinateChar != ' ') {
				std::shared_ptr<Boat> boat = ownerBoard->getBoatAt(Coordinate(coor.row, coor.col-1, coor.depth));
				checkAdjacentBoat(boat, coor, size, 2, player, ownerBoard, rivalBoard);
			}
		}

		if (coor.depth > 0) {
			char behindCoordinateChar = this->board.at(coor.depth-1).at(coor.row).at(coor.col);
			if (behindCoordinateChar != ' ') {
				std::shared_ptr<Boat> boat = ownerBoard->getBoatAt (Coordinate(coor.row, coor.col, coor.depth-1));
				checkAdjacentBoat(boat, coor, size, 3, player, ownerBoard, rivalBoard);
			}
		}
	}
}

bool Board::thereIsABoatNearby(Coordinate coor){
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

void Board::checkAdjacentBoat(std::shared_ptr<Boat> boat, Coordinate coor, int size, int direction, int player, std::shared_ptr<PlayerBoard> ownerBoard, std::shared_ptr<PlayerBoard> rivalBoard) {
	if (boat->getBoatSize() == size && boat->getPlayer() == player) {
		if (boat->getDirection() == 0) {
			boat->setDirection(direction);
		}
		//same boat, merge needed
		if (ownerBoard->getBoatAt(coor) != nullptr) {
			//there is already a boat at point
			if (ownerBoard->getBoatAt(coor) != boat) {
				mergeBoats(boat, ownerBoard->getBoatAt(coor), direction, ownerBoard);
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
		if (ownerBoard->getBoatAt(coor) == nullptr) {
			std::shared_ptr<Boat> newBoat = std::make_shared<Boat>(size, player, ownerBoard, rivalBoard, coor);
		}
		this->hasAdjacentBoats = true;
	}
}

void Board::mergeBoats(std::shared_ptr<Boat> boat1, std::shared_ptr<Boat> boat2, int direction, std::shared_ptr<PlayerBoard> ownerBoard) {

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
}

//checking that all boats are of correct size and shape
void Board::checkBoatValidity() {
	for (int dep = 0; dep < this->depth; dep++) {
		for (int row = 0; row < this->numOfRows; row++) {
			for (int col = 0; col < this->numOfCols; col++) {

				Coordinate point = Coordinate(row, col, dep);
				std::shared_ptr<Boat> boat = nullptr;

				boat = this->playerABoard->getBoatAt(point);

				if (boat == nullptr) {
					boat = this->playerBBoard->getBoatAt(point);
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
					}
				}
			}
		}
	}
}

bool Board::checkBoard() {
	bool result = true;

	if (this->errorArray[0]) {
		this->logger->logMessage("Wrong size or shape for ship B for player A");
		result = false;
	}
	if (this->errorArray[1]) {
		this->logger->logMessage("Wrong size or shape for ship P for player A");
		result = false;
	}
	if (this->errorArray[2]) {
		this->logger->logMessage("Wrong size or shape for ship M for player A");
		result = false;
	}
	if (this->errorArray[3]) {
		this->logger->logMessage("Wrong size or shape for ship D for player A");
		result = false;
	}
	if (this->errorArray[4]) {
		this->logger->logMessage("Wrong size or shape for ship b for player B");
		result = false;
	}
	if (this->errorArray[5]) {
		this->logger->logMessage("Wrong size or shape for ship p for player B");
		result = false;
	}
	if (this->errorArray[6]) {
		this->logger->logMessage("Wrong size or shape for ship m for player B");
		result = false;
	}
	if (this->errorArray[7]) {
		this->logger->logMessage("Wrong size or shape for ship d for player B");
		result = false;
	}
	return result;
}

BoardData& Board::getPlayerBoard (int player){
	if(player == 0){
		return this->playerABoard;
	}
	else if (player == 1) {
		return this->playerBBoard;
	}
	else {
		return nullptr;
	}
}

int Board::getGameScore(int player){
	if(player == 0){
		return this->playerAScore;
	}
	else if (player==1){
		return this->playerBScore;
	}
	else{
		return -1;
	}

}

void Board::handleSunkBoat (int owner, int value){

}
