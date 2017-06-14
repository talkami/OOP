#include "PlayerBoard.h"

void PlayerBoard::setVars(int rows, int cols, int depth, int player) {
	//you cannot initialize base class members from initializer list directly
	this->_rows = rows;
	this->_cols = cols;
	this->_depth = depth;
	this->playerNum = player;

	board.resize(this->_depth);
	for (int i = 0; i < this->_depth; i++) {
		board.at(i).resize(this->_rows);
		for (int j = 0; j < this->_rows; j++) {
			board.at(i).at(j).resize(this->_cols);
		}
	}
}

void PlayerBoard::loadBoard(const BoardData& boardData, int player) {
	setVars(boardData.rows(), boardData.cols(), boardData.depth(), player);
	for (int dep = 0; dep < this->_depth; dep++) {
		for (int row = 0; row < this->_rows; row++) {
			for (int col = 0; col < this->_cols; col++) {
				char currChar = boardData.charAt(Coordinate(row + 1, col + 1, dep + 1));
				setChar(Coordinate(row, col, dep), currChar);
			}
		}
	}
}

char PlayerBoard::charAt(Coordinate c) const{
	if (invalidCoordinate(c)) {
		return ' ';
	}
	char currChar = this->board.at(c.depth-1).at(c.row-1).at(c.col-1);
	if (currChar == 'i' || currChar == 'e') {//invalid char
		return ' ';
	}
	else {
		return currChar;
	}	
}

void PlayerBoard::setChar(Coordinate coor, char ch) {
	editBoardAtPoint(coor, ch);
	if (ch == 'B' || ch == 'b') {
		this->boatsCount[0] += 1;
		setInvalidArea(coor);
	}
	else if (ch == 'P' || ch == 'p') {
		this->boatsCount[1] += 1;
		setInvalidArea(coor);
	}
	else if (ch == 'M' || ch == 'm') {
		this->boatsCount[2] += 1;
		setInvalidArea(coor);
	}
	else if (ch == 'D' || ch == 'd') {
		this->boatsCount[3] += 1;
		setInvalidArea(coor);
	}
}

bool PlayerBoard::invalidCoordinate(Coordinate c) const {
	if (c.row <= 0 || c.col <= 0 || c.depth <= 0) {
		return true;
	}
	if (c.row > this->_rows || c.col > this->_cols || c.depth > this->_depth) {
		return true;
	}
	return false;
}

void PlayerBoard::editBoardAtPoint(Coordinate point, char charAtPoint){
	if (!invalidCoordinate(point)) {
		this->board.at(point.depth).at(point.row).at(point.col) = charAtPoint;		
	}
}

bool PlayerBoard::isValidToExplorationAttack(Coordinate coor){
	if (charAt(coor) == ' '){
		return true;
	}
	else{ 
		return false;
	}
}

void PlayerBoard::invalidateExplorationAttackArea(Coordinate c, int smallestBoat){
	editBoardAtPoint(c, 'e');
	for (int i = 1; i < smallestBoat; i++) {
		editBoardAtPoint(Coordinate(c.row+i, c.col, c.depth), 'e');
		editBoardAtPoint(Coordinate(c.row-i, c.col, c.depth), 'e');
		editBoardAtPoint(Coordinate(c.row, c.col+i, c.depth), 'e');
		editBoardAtPoint(Coordinate(c.row, c.col-i, c.depth), 'e');
		editBoardAtPoint(Coordinate(c.row, c.col, c.depth+i), 'e');
		editBoardAtPoint(Coordinate(c.row, c.col, c.depth-i), 'e');
	}
}

void PlayerBoard::setInvalidHorizontal(Coordinate coor) {
	editBoardAtPoint(Coordinate(coor.row-1, coor.col, coor.depth), 'i');
	editBoardAtPoint(Coordinate(coor.row+1, coor.col, coor.depth), 'i');
}

void PlayerBoard::setInvalidVertical(Coordinate coor) {
	editBoardAtPoint(Coordinate(coor.row, coor.col-1, coor.depth), 'i');
	editBoardAtPoint(Coordinate(coor.row, coor.col+1, coor.depth), 'i');
}

void PlayerBoard::setInvalidDepth(Coordinate coor) {
	editBoardAtPoint(Coordinate(coor.row, coor.col, coor.depth-1), 'i');
	editBoardAtPoint(Coordinate(coor.row, coor.col, coor.depth+1), 'i');
}

void PlayerBoard::setInvalidArea(Coordinate coor) {
	editBoardAtPoint(coor, 'i');
	setInvalidHorizontal(coor);
	setInvalidVertical(coor);
	setInvalidDepth(coor);
}

bool PlayerBoard::isValidAttack (Coordinate coor){
	char currChar = this->board.at(coor.depth).at(coor.row).at(coor.col);
	if (currChar == 'i'){
		return false;
	}
	else{
		return true;
	}
}

void PlayerBoard::setInvalidAttack (Coordinate coor){
	editBoardAtPoint(coor, 'i');
}
