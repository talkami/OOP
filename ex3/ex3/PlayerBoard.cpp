
	
	
	virtual char PlayerBoard::charAt(Coordinate c) const{
		char tmp = this->_board[c.getCol()][c.getRow()][c.getDepth()];
		return tmp;
	}

	//new funcs
	void PlayerBoard::addBoat(Boat * boat){
		this->boats.push_back (boat);
		this-> numOfPlayerBoats = this->numOfPlayerBoats+1;
	}

	Boat* PlayerBoard::getBoatAt (int row, int col, int depth){
	//stackoverflow says it works
		for(std::vector<T>::iterator boat = this->boats.begin(); boat != boats.end(); ++boat) {
			for(std::vector<T>::iterator coor = boat->getCoordinatesArray().begin(); coor != boats.end(); ++coor){
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
		this->_board.at(depth).at(rows).at(cols) = characterAtPoint;
	}

	void PlayerBoard::loadBoard (BoardData* board){
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
