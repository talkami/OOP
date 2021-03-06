#include "GameBoard.h"

GameBoard::GameBoard(int _rows, int _cols, int _depth, std::vector<std::shared_ptr<Boat>> boats) :
						rows(_rows), cols(_cols), depth(_depth) {
	for (std::shared_ptr<Boat> boat : boats) {
		if (boat->getPlayer()) {
			this->playerBBoats.push_back(boat->getNewCopy());
		}
		else {
			this->playerABoats.push_back(boat->getNewCopy());
		}
	}
}

int GameBoard::getGameScore(int player) {
	return this->scores[player];
}

AttackResult GameBoard::attack(Coordinate coor, int attacker, bool* selfHit) {
	if(coor.row <= 0 || coor.col <= 0 || coor.depth <= 0 ||
		coor.row > this->rows || coor.col > this->cols || coor.depth > this->depth) {
		return AttackResult::Miss;
	}
	AttackResult res = AttackResult::Miss;
	if (attacker) {
		res = checkABoats(Coordinate(coor.row - 1, coor.col - 1, coor.depth - 1), attacker, selfHit);
		if (res == AttackResult::Miss) {
			res = checkBBoats(coor, attacker, selfHit);
		}
		return res;
	}
	else {
		res = checkBBoats(Coordinate(coor.row - 1, coor.col - 1, coor.depth - 1), attacker, selfHit);
		if (res == AttackResult::Miss) {
			res = checkABoats(coor, attacker, selfHit);
		}
		return res;
	}
}

AttackResult GameBoard::checkABoats(Coordinate coor, int attacker, bool* selfHit) {
	for (int i = 0; i < this->playerABoats.size(); i++) {
		std::shared_ptr<Boat> boat = this->playerABoats.at(i);
		if (boat->containsPoint(coor)) {
			*selfHit = attacker == 0 ? true : false;
			int value = boat->addHit(coor);
			if (value == 0) {
				return AttackResult::Hit;
			}
			else {
				this->scores[1] += value;
				this->playerABoats.erase(this->playerABoats.begin() + i);
				return AttackResult::Sink;
			}
		}
	}
	return AttackResult::Miss;
}

AttackResult GameBoard::checkBBoats(Coordinate coor, int attacker, bool* selfHit) {
	for (int i = 0; i < this->playerBBoats.size(); i++) {
		std::shared_ptr<Boat> boat = this->playerBBoats.at(i);
		if (boat->containsPoint(coor)) {
			*selfHit = attacker == 1 ? true : false;
			int value = boat->addHit(coor);
			if (value == 0) {
				return AttackResult::Hit;
			}
			else {
				this->scores[0] += value;
				this->playerBBoats.erase(this->playerBBoats.begin() + i);
				return AttackResult::Sink;
			}
		}
	}
	return AttackResult::Miss;
}

bool GameBoard::AIsOutOfBoats() {
	return this->playerABoats.empty();
}

bool GameBoard::BIsOutOfBoats() {
	return this->playerBBoats.empty();
}
