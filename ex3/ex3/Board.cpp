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
	 vector<vector<vector<char>>> A(this->col, vector<char>(this->row), vector<vector<char>>(this->depth));
	 this->playerABoard = A;
	 vector<vector<vector<char>>> B(this->col, vector<char>(this->row), vector<vector<char>>(this->depth));
	 this->playerBBoard = B;

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
//maybe dont need it

//checking the char read from the file and putting the boat on the board
void GameBoard::addToPlayerBoard(char currentChar, int row, int col, int depth) {

	if (currentChar == 'B') {
		addBoatToBoard(row, col, depth 1, 0);
		this->playerABoard.at(depth).at(row).at(col) = 'B';
		this->board.at(depth).at(row).at(col) = 'B';
	}
	else if (currentChar == 'b') {
		addBoatToBoard(this->matrix[row][col], 1, 1, B, A);
		this->playerBBoard.at(depth).at(row).at(col) = 'b';
		this->board.at(depth).at(row).at(col) = 'b';

	}
	else if (currentChar == 'P') {
		addBoatToBoard(this->matrix[row][col], 2, 0, A, B);
		this->playerABoard.at(depth).at(row).at(col) = 'P';
		this->board.at(depth).at(row).at(col) = 'P';
	}
	else if (currentChar == 'p') {
		addBoatToBoard(this->matrix[row][col], 2, 1, B, A);
		this->playerBBoard.at(depth).at(row).at(col) = 'p';
		this->board.at(depth).at(row).at(col) = 'p';
	}
	else if (currentChar == 'M') {
		addBoatToBoard(this->matrix[row][col], 3, 0, A, B);
		this->playerABoard.at(depth).at(row).at(col) = 'M';
		this->board.at(depth).at(row).at(col) = 'M';
	}
	else if (currentChar == 'm') {
		addBoatToBoard(this->matrix[row][col], 3, 1, B, A);
		this->playerBBoard.at(depth).at(row).at(col) = 'm';
		this->board.at(depth).at(row).at(col) = 'm';
	}
	else if (currentChar == 'D') {
		addBoatToBoard(this->matrix[row][col], 4, 0, A, B);
		this->playerABoard.at(depth).at(row).at(col) = 'D';
		this->board.at(depth).at(row).at(col) = 'D';
	}
	else if (currentChar == 'd') {
		addBoatToBoard(this->matrix[row][col], 4, 1, B, A);
		this->playerBBoard.at(depth).at(row).at(col) = 'd';
		this->board.at(depth).at(row).at(col) = 'd';
	}
}

void Board::addBoatToBoard(int row, int col, int depth, int size, int player, IBattleshipGameAlgo* owner, IBattleshipGameAlgo* rival) {
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


void Board::checkAdjacentBoat(Boat* boat, int row, int col, int depth, int size, int direction, int player, IBattleshipGameAlgo* owner, IBattleshipGameAlgo* rival) {
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
void GameBoard::checkBoatValidity() {
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			Boat* boat = this->matrix[i][j]->getBoat();
			if (boat != nullptr) {
				if ((boat->getBoatSize() != boat->getAcctualSize()) || !boat->isValid()) {
					int errorNum = (boat->getBoatSize() - 1) + (4 * boat->getPlayer());
					errorArray[errorNum] = true;
					if (boat->getPlayer() == 0) {
						this->PlayerANumOfBoats--;
					}
					else if (boat->getPlayer() == 1) {
						this->PlayerBNumOfBoats--;
					}
					delete boat;
				}
			}
		}
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
bool GameBoard::checkNumOfPlayersBoats(IBattleshipGameAlgo* A, IBattleshipGameAlgo* B) {
	bool result = true;
	if (this->PlayerANumOfBoats < 5) {
		result = false;
		std::cout << "Too few ships for player A" << std::endl;
	}
	if (this->PlayerANumOfBoats > 5) {
		result = false;
		std::cout << "Too many ships for player A" << std::endl;
	}
	if (this->PlayerBNumOfBoats < 5) {
		result = false;
		std::cout << "Too few ships for player B" << std::endl;
	}
	if (this->PlayerBNumOfBoats > 5) {
		result = false;
		std::cout << "Too many ships for player B" << std::endl;
	}
	return result;
}

// attack function - get pair and attack at the <x,y> point in the "matrix" variable.
AttackResult GameBoard::play_attack(std::pair<int, int> attack, int attacker, bool* selfHit) {
	if (attack.first == -1 || attack.second == -1) {
		return AttackResult::Miss;
	}
	int row = attack.first - 1;
	int col = attack.second - 1;
	AttackResult result = this->matrix[row][col]->attack(attacker, selfHit);
	if (result == AttackResult::Sink){
		removeBoat (this->matrix[row][col]->getBoat()->getPlayer());
		increaseScore(this->matrix[row][col]->getBoat()->getValue(),this->matrix[row][col]->getBoat()->getPlayer());		
	}
	return result;
}

char** GameBoard::getPlayerABoard() {
	return this->playerABoard;
}
char** GameBoard::getPlayerBBoard() {
	return this->playerBBoard;
}

void GameBoard::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void GameBoard::setTextColor(int color) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, color);
}

void GameBoard::hideCursor() {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hConsole, &ConCurInf);
}

void GameBoard::addToDisplay(int x, int y, int color, char c) {
	setTextColor(color);
	gotoxy(x, y);
	std::cout << c;
}

void GameBoard::displayBoard() {
	system("cls");
	hideCursor();
	for (int i = 0; i < this->numOfRows; i++) {
		for (int j = 0; j < this->numOfCols; j++) {
			Boat* boat = this->matrix[i][j]->getBoat();
			if (boat != nullptr) {
				addToDisplay(j, i, this->colors[boat->getPlayer()], ' ');
			}
		}
	}
}

void GameBoard::displayAttack(AttackResult result, int row, int col, int delay) {
	Boat* boat = this->matrix[row - 1][col - 1]->getBoat();
	if (result != AttackResult::Miss) {
		addToDisplay(col - 1, row - 1, this->colors[boat->getPlayer()], 'X');
		if (result == AttackResult::Sink) {
			sinkBoatAnimation(boat, this->colors[boat->getPlayer()], delay);
			return;
		}
		Sleep(delay);
	}
}

void GameBoard::sinkBoatAnimation(Boat* boat, int color, int delay) {
	std::vector<std::pair<int, int>> points = boat->getPoints();
	Sleep(delay / 2);
	for (int i = 0; i < points.size(); i++) {
		addToDisplay(points[i].second, points[i].first, color, '@');
		Sleep(delay / 2);
	}
	for (int i = 0; i < points.size(); i++) {
		addToDisplay(points[i].second, points[i].first, 0, ' ');
	}
	Sleep(delay);
}

//new funcs
bool GameBoard :: hasNoMoreBoats(int player){
	if (this->PlayerANumOfBoats==0 && player==0){
		return true;
	}
	else if (this->PlayerBNumOfBoats==0 && player==1){
		return true;
	}
	else{
		return false;
	}
}


void GameBoard :: removeBoat(int player){
	if (player==0){
		this->PlayerANumOfBoats--;
	}
	else if (player==1){
		this->PlayerBNumOfBoats--;
	}
}
	
int GameBoard ::getNumOfBoats(int player){
	if (player==0){
		return this->PlayerANumOfBoats;
	}
	else if (player==1){
		return this->PlayerBNumOfBoats;
	}
}
	
int GameBoard :: getGameScore(int player){
	if (player==0){
		return this->PlayerAScore;
	}
	else if (player==1){
		return this->PlayerBScore;
	}
}
	
void GameBoard:: increaseScore(int amount, int player){
	if (player==1){
		this->PlayerAScore= this->PlayerAScore + amount;
	}
	else if (player==0){
		this->PlayerBScore= this->PlayerBScore + amount;
	}
}