#include "PlayerBoard.h"

PlayerBoard::PlayerBoard(int rows, int cols, int depth) {
	_rows = rows;
	_cols = cols;
	_depth = depth;
}

PlayerBoard::PlayerBoard(int rows, int cols, int depth, std::vector<std::vector<std::vector<char>>> board, int player) :
	_board(board), _player(player) {
	PlayerBoard(rows, cols, depth);
}

char PlayerBoard::charAt(Coordinate c) const{
	if (invalidCoordinate(c)) {
		return ' ';
	}
	char currChar = this->_board.at(c.depth-1).at(c.row-1).at(c.col-1);
	if (currChar == 'I') {//invalid char
		return ' ';
	}
	else {
		return currChar;
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

//new funcs
void PlayerBoard::addBoat(Boat * boat){
	this->boats.push_back (boat);
	this-> numOfPlayerBoats = this->numOfPlayerBoats+1;
	this->boatsCount[boat->getSize()-1] ++;
}

Boat* PlayerBoard::getBoatAt (int row, int col, int depth){
//stackoverflow says it works
		for(std::vector	for(std::vector<T>::iterator boat = this->boats.begin(); boat != boats.end(); ++boat) {
<T>::iterator coor = boat->getCoordinatesArray().begin(); coor != boats.end(); ++coor){
			if (coor->getCol()== col && coor->getRow()== row && coor->getDepth()== depth ){
				return boat;
			}
		}
	}
	return nullptr;


}
void PlayerBoard::removeBoat(Boat* boat){
	this->boats.erase(std::remove(boats.begin(), boats.end(), boat), boats.end()); 
	this-> numOfPlayerBoats = this->numOfPlayerBoats-1;
	this->boatsCount[boat->getSize()-1] --;

	//stackoverflow says its works
}
bool PlayerBoard::isThereMoreBoats (){
	if(numOfPlayerBoats==0){
		return true;
	}
	else {
		return false;
	}
}
void PlayerBoard::editBoardAtPoint (int rows, int cols, int depth, char characterAtPoint){
	if (rows>0 && rows< this->_rows && cols>0 && cols< this->_cols && depth >0 && depth < this->_depth){
		this->_board.at(depth).at(rows).at(cols) = characterAtPoint;
	}
}

void PlayerBoard::loadBoard (const BoardData& board){
	for (int col =0; col<board->cols(); col++){
		for (int row =0; row<board->rows(); row++){
			for (int depth =0; depth<board->depth(); depth++){
					this-> editBoardAtPoint(row,col,depth, board->charAt(Coordinate(row,col,depth)));
			}
		}
	}
}

std::pair<AttackResult,int> PlayerBoard::attack (Coordinate coor){
	Boat* tmpBoat = nullptr;
	tmpBoat = this->getBoatAt (coor);
	if (tmpBoat == nullptr){
		return <Miss,0>;
	}
	else{
		int val = tmpBoat->addHit (coor);
		if (val == 0){
			return <Hit,0>;
		}
		else{
			return <Sink, val>;
		}
	}
}


bool PlayerBoard::isValidAttack (Coordinate coor){
	
}

void PlayerBoard::setInvalidAttack (Coordinate coor){
	
}

void PlayerBoard::setInvalidArea (Coordinate coor){
	
}

void PlayerBoard::setInvalidHorizontal (){
	
}
int* PlayerBoard::getBoatsCount(){
	return this->boatsCount;
}

bool PlayerBoard::isValidToExplorationAttack(Coordinate coor){
	if (charAt (coor) == ' '){
		return true;
	}
	else{ 
		return false;
	}
}

void invalidateExplorationAttackArea(int row, int col, int depth, int smallestBoat){
	editBoardAtPoint(row,col,depth, 'e');
	for (int i =1 ;i<smallestBoat; i ++){
		editBoardAtPoint(row+i, col, depth, 'e');
		editBoardAtPoint(row-i, col, depth, 'e');
		editBoardAtPoint(row, col+i, depth, 'e');
		editBoardAtPoint(row, col-i, depth, 'e');
		editBoardAtPoint(row, col, depth+i, 'e');
		editBoardAtPoint(row, col, depth-i, 'e');
	}
}
