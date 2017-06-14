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

char PlayerBoard::charAt(Coordinate c) const{
	if (invalidCoordinate(c)) {
		return ' ';
	}
	char currChar = this->board.at(c.depth).at(c.row).at(c.col);
	if (currChar == 'i' || currChar == 'e') {//invalid char
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
void PlayerBoard::addBoat(std::shared_ptr<Boat> boat){
	this->boats.push_back (boat);
	this-> numOfPlayerBoats = this->numOfPlayerBoats+1;
	this->boatsCount[(boat->getSize())-1] += 1;
}

std::shared_ptr<Boat> PlayerBoard::getBoatAt (Coordinate coor){
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
void PlayerBoard::removeBoat(std::shared_ptr<Boat> boat){
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
void PlayerBoard::editBoardAtPoint (Coordinate coor, char characterAtPoint){
	if (rows>0 && rows< this->_rows && cols>0 && cols< this->_cols && depth >0 && depth < this->_depth){
		this->_board.at(depth).at(rows).at(cols) = characterAtPoint;
	}
}

void PlayerBoard::loadBoard(const BoardData& board){
	for (int col =0; col<board.cols(); col++){
		for (int row =0; row<board.rows(); row++){
			for (int depth =0; depth<board.depth(); depth++){
				Coordinate point = Coordinate(row, col, depth);
					editBoardAtPoint(point, board.charAt(point));
			}
		}
	}
}

std::pair<AttackResult,int> PlayerBoard::attack (Coordinate coor){
	std::shared_ptr<Boat> tmpBoat = nullptr;
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
	editBoardAtPoint(Coordinate(row,col,depth), 'e');
	for (int i =1 ;i<smallestBoat; i ++){
		editBoardAtPoint(row+i, col, depth, 'e');
		editBoardAtPoint(row-i, col, depth, 'e');
		editBoardAtPoint(row, col+i, depth, 'e');
		editBoardAtPoint(row, col-i, depth, 'e');
		editBoardAtPoint(row, col, depth+i, 'e');
		editBoardAtPoint(row, col, depth-i, 'e');
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerBoard::setInvalidHorizontal(Coordinate coor) {
	editBoardAtPoint(coor.row-1, coor.col, coor.depth, 'i');
	editBoardAtPoint(coor.row+1, coor.col, coor.depth, 'i');
}

void PlayerBoard::setInvalidVertical(Coordinate coor) {
	editBoardAtPoint(coor.row, coor.col-1, coor.depth, 'i');
	editBoardAtPoint(coor.row, coor.col+1, coor.depth, 'i');
}
void PlayerBoard::setInvalidDepth(Coordinate coor) {
	editBoardAtPoint(coor.row, coor.col, coor.depth-1, 'i');
	editBoardAtPoint(coor.row, coor.col, coor.depth+1, 'i');
}
void PlayerBoard::setInvalidArea(Coordinate coor) {
	setInvalidHorizontal(coor);
	setInvalidVertical(coor);
	setInvalidDepth(coor);
}

bool PlayerBoard::isValidAttack (Coordinate coor){
	char currChar = this->_board.at(coor.depth).at(coor.row).at(coor.col);
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
