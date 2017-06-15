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
		for (std::vector<Boat>::iterator boat = boats.begin(); boat != boats.end(); ++boat) {
			if (boat.containsPoint(coor) {
				int value = boat.addHit(coor);
				if (value == 0) {
					return Hit;
				}
				else {
					this->playerBScore = this->playerBScore + value;
					//remove boat
					return Sink;

				}
			}
		}
		for (std::vector<Boat>::iterator boat = boats.begin(); boat != boats.end(); ++boat) {
			if (boat.containsPoint(coor) {
				int value = boat.addHit(coor);
				if (value == 0) {
					return Hit;
				}
				else {
					this->playerBScore = this->playerAScore + value;
					return Sink;

				}
			}
		}
		return Miss;
	}
	else {

	}
}

void handleSunkBoat(int owner, int value);