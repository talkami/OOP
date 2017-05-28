#include "GameBoard.h"



GameBoard::~GameBoard() {
	for (int i = 0; i < this->numOfRows; i++) {
		delete[]this->playerABoard[i];
		delete[]this->playerBBoard[i];
	}
	delete[]this->playerABoard;
	delete[]this->playerBBoard;
}

bool GameBoard::initBoard(const std::string& path, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B, int rows, int cols, bool display) {
	bool result = true;
	this->numOfRows = rows;
	this->numOfCols = cols;
	this->display = display;
	this->PlayerAScore = 0;
	this-> PlayerBScore = 0;
	this-> PlayerANumOfBoats = 0;
	this-> PlayerBNumOfBoats=0;
	
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
		result = loadBoard(boardFileLister.getFilesList()[0], A, B);
	}
	return result;
}

//load GameBoard function
bool GameBoard::loadBoard(const std::string& boardFile, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B) {
	bool result = true;
	setVars();

	std::ifstream fin(boardFile);
	if (!fin) {
		std::cout << "Error reading from file: " << boardFile << std::endl;
		return false;
	}

	for (int i = 0; i < this->numOfRows; i++) {
		std::string buffer;
		std::getline(fin, buffer);
		for (int j = 0; j < this->numOfCols; j++) {
			char currChar = ' ';
			if (j < buffer.length()) {
				currChar = buffer.at(j);
			}
			setPoint(i, j);
			addToPlayerBoard(currChar, i, j, A, B);
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

void GameBoard::setVars() {
	Board::setVars();

	this->playerABoard = new char *[this->numOfRows];
	this->playerBBoard = new char *[this->numOfRows];

	for (int i = 0; i < this->numOfRows; i++) {
		this->playerABoard[i] = new char[this->numOfCols];
		this->playerBBoard[i] = new char[this->numOfCols];
		memset(playerABoard[i], ' ', numOfCols);
		memset(playerBBoard[i], ' ', numOfCols);
	}

}

//checking the char read from the file and putting the boat on the board
void GameBoard::addToPlayerBoard(char currentChar, int row, int col, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B) {

	if (currentChar == 'B') {
		addBoatToBoard(this->matrix[row][col], 1, 0, A, B);
		this->playerABoard[row][col] = 'B';
	}
	else if (currentChar == 'b') {
		addBoatToBoard(this->matrix[row][col], 1, 1, B, A);
		this->playerBBoard[row][col] = 'b';

	}
	else if (currentChar == 'P') {
		addBoatToBoard(this->matrix[row][col], 2, 0, A, B);
		this->playerABoard[row][col] = 'P';
	}
	else if (currentChar == 'p') {
		addBoatToBoard(this->matrix[row][col], 2, 1, B, A);
		this->playerBBoard[row][col] = 'p';
	}
	else if (currentChar == 'M') {
		addBoatToBoard(this->matrix[row][col], 3, 0, A, B);
		this->playerABoard[row][col] = 'M';
	}
	else if (currentChar == 'm') {
		addBoatToBoard(this->matrix[row][col], 3, 1, B, A);
		this->playerBBoard[row][col] = 'm';
	}
	else if (currentChar == 'D') {
		addBoatToBoard(this->matrix[row][col], 4, 0, A, B);
		this->playerABoard[row][col] = 'D';
	}
	else if (currentChar == 'd') {
		addBoatToBoard(this->matrix[row][col], 4, 1, B, A);
		this->playerBBoard[row][col] = 'd';
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