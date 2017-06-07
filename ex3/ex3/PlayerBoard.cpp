	
	
	
	virtual char PlayerBoard::charAt(Coordinate c) const{
	
	}

	//new funcs

	void PlayerBoard::addBoat(Boat * boat){
		this->boats.push_back (boat);
		this-> numOfPlayerBoats = this->numOfPlayerBoats+1;
	}

	Boat* PlayerBoard::getBoatAt (int row, int col, int depth){
	
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