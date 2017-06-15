#include "gameBoard.h"

gameBoard(std::vector<std::shared_ptr<Boat>> boats) {
	this-> playerAScore = 0;
	this-> playerBScore = 0;
	for (std::vector<Boat>::iterator boat = boats.begin(); boat != boats.end(); ++boat) {
		if (boat.getPlayer()) {
			this->playerBboats.push_back(boat);
		}
		else {
			this->playerAboats.push_back(boat);
		}
	}
}
int getGameScore(int player) {
	if (player) {
		return this->playerBScore;
	}
	else {
		return this->playerAScore;
	}
}

bool hasNoMoreBoats(int player) {
	if (player) {
		return this->playerBboats.empty();
	}
	else {
		return this->playerBboats.empty();
	}
}

AttackResult attack(Coordinate coor, int attacker, bool* selfHit) {
	if (attacker) {
		for (std::vector<Boat>::iterator boat = playerAboats.begin(); boat != playerAboats.end(); ++boat) {
			if (boat.containsPoint(coor) {
				int value = boat.addHit(coor);
				if (value == 0) {
					return Hit;
				}
				else {
					this->playerAScore = this->playerAScore + value;
					playerAboats.erase(std::remove(playerAboats.begin(), playerAboats.end(), boat), playerAboats.end()); 

					return Sink;

				}
			}
		}
		for (std::vector<Boat>::iterator boat = playerBboats.begin(); boat != playerBboats.end(); ++boat) {
			if (boat.containsPoint(coor) {
				int value = boat.addHit(coor);
				if (value == 0) {
					selfHit* = true;
					return Hit;
				}
				else {
					this->playerBScore = this->playerBScore + value;
					selfHit* = true;
					playerBboats.erase(std::remove(playerBboats.begin(), playerBboats.end(), boat), playerBboats.end()); 
					return Sink;

				}
			}
		}
		return Miss;
	}
	else {
		for (std::vector<Boat>::iterator boat = playerBboats.begin(); boat != playerBboats.end(); ++boat) {
			if (boat.containsPoint(coor) {
				int value = boat.addHit(coor);
				if (value == 0) {
					return Hit;
				}
				else {
					this->playerBScore = this->playerBScore + value;
					playerBboats.erase(std::remove(playerBboats.begin(), playerBboats.end(), boat), playerBboats.end()); 
					return Sink;

				}
			}
		}
		for (std::vector<Boat>::iterator boat = playerAboats.begin(); boat != playerAboats.end(); ++boat) {
			if (boat.containsPoint(coor) {
				int value = boat.addHit(coor);
				if (value == 0) {
					selfHit* = true;
					return Hit;
				}
				else {
					this->playerAScore = this->playerAScore + value;
					selfHit* = true;
					playerAboats.erase(std::remove(playerAboats.begin(), playerAboats.end(), boat), playerAboats.end()); 
					return Sink;

				}
			}
		}
		return Miss;
	}
}




bool gameBoard::playerAOutOfBoats (){
	return this->playerAboats.empty();
}
bool gameBoard::playerBOutOfBoats (){
	return this->playerBboats.empty();
}