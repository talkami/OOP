#include "PlayerBoard.h"

void PlayerBoard::setVars(int rows, int cols, int depth, int player) {
	this->_rows = rows;
	this->_cols = cols;
	this->_depth = depth;
	this->playerNum = player;

	board.resize(this->_depth);
	for (int i = 0; i < this->_depth; i++) {
		board.at(i).resize(this->_rows);
		for (int j = 0; j < this->_rows; j++) {
			board.at(i).at(j).resize(this->_cols, ' ');
		}
	}
}

void PlayerBoard::loadBoard(const BoardData& boardData, int player) {
	setVars(boardData.rows(), boardData.cols(), boardData.depth(), player);
	for (int dep = 0; dep < this->_depth; dep++) {
		for (int row = 0; row < this->_rows; row++) {
			for (int col = 0; col < this->_cols; col++) {
				char currChar = boardData.charAt(Coordinate(row + 1, col + 1, dep + 1));
				editBoardAtPoint(Coordinate(row, col, dep), currChar);
				if (currChar == 'b' || currChar == 'B' || currChar == 'p' || currChar == 'P' ||
					currChar == 'm' || currChar == 'M' || currChar == 'd' || currChar == 'D') {
					setInvalidArea(Coordinate(row, col, dep));
				}				
			}
		}
	}
}

char PlayerBoard::charAt(Coordinate c) const{
	if (invalidCoordinate(Coordinate(c.row - 1, c.col - 1, c.depth - 1))) {
		return ' ';
	}
	char currChar = this->board.at(c.depth-1).at(c.row-1).at(c.col-1);
	if (currChar == 'i') {//invalid char
		return ' ';
	}
	else {
		return currChar;
	}	
}

bool PlayerBoard::invalidCoordinate(Coordinate c) const {
	if (c.row < 0 || c.col < 0 || c.depth < 0) {
		return true;
	}
	if (c.row >= this->_rows || c.col >= this->_cols || c.depth >= this->_depth) {
		return true;
	}
	return false;
}

void PlayerBoard::editBoardAtPoint(Coordinate point, char charAtPoint){
	if (!invalidCoordinate(point)) {
		this->board.at(point.depth).at(point.row).at(point.col) = charAtPoint;		
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
	setInvalidHorizontal(coor);
	setInvalidVertical(coor);
	setInvalidDepth(coor);
}

bool PlayerBoard::isValidAttack (Coordinate coor){
	if (invalidCoordinate(coor)) {
		return false;
	}
	char currChar = this->board.at(coor.depth).at(coor.row).at(coor.col);
	if (currChar == 'i') {
		return false;
	}
	else if (currChar == 'b' || currChar == 'B' || currChar == 'p' || currChar == 'P' ||
		currChar == 'm' || currChar == 'M' || currChar == 'd' || currChar == 'D') {
		return false;
	}
	else {
		return true;
	}
}

void PlayerBoard::setInvalidAttack(Coordinate coor){
	editBoardAtPoint(coor, 'i');
}