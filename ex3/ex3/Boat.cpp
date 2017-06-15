#include "Boat.h"

Boat::Boat(int size, int _player, Coordinate firstPoint) : boatSize(size), direction(0), acctualSize(1),
			hits(0), player(_player), validity(true) {
	this->coordinatesArray.push_back(firstPoint);
	this->value = setValue(size);
}

int Boat::getNumOftHits() {
	return this->hits;
}
int Boat::getDirection() {
	return this->direction;
}
int Boat::getPlayer() {
	return this->player;
}
int Boat::getBoatSize() {
	return this->boatSize;
}
int Boat::getAcctualSize() {
	return this->acctualSize;
}

bool Boat::isSunk() {
	if (hits == boatSize) {
		return true;
	}
	else {
		return false;
	}
}

int Boat::getValue() {
	return this->value;
}

bool Boat::isValid() {
	return this->validity;
}

void Boat::addPoint(Coordinate point) {
	this->coordinatesArray.push_back(point);
	this->acctualSize++;
}

void Boat::setDirection(int direction) {
	this->direction = direction;
}

void Boat::setValidity(bool validity) {
	this->validity = validity;
}

void Boat::mergeBoats(std::shared_ptr<Boat> boat) {
	std::vector<Coordinate> otherPoints = boat->coordinatesArray;
	this->acctualSize += boat->acctualSize;
	this->coordinatesArray.insert(this->coordinatesArray.end(), otherPoints.begin(), otherPoints.end());
}

int Boat::setValue(int size) {
	if (size == 1) {
		return 2;
	}
	if (size == 2) {
		return 3;
	}
	if (size == 3) {
		return 7;
	}
	if (size == 4) {
		return 8;
	}
	else {
		return -1;
	}
}

//remove coor from boat, return value if sunk. we assume the coor is inside the boat coordinatesArray
int Boat::addHit(Coordinate coor){
	for (int i = 0; i < this->coordinatesArray.size(); i++) {
		Coordinate point = this->coordinatesArray.at(i);
		if (coor.col == point.col && coor.row == point.row && coor.depth == point.depth) {
			this->coordinatesArray.erase(this->coordinatesArray.begin() + i);
		}
	}
	this->hits += 1;
	if (this->isSunk()){
		return this->value;
	}
	else {
		return 0;
	}
}

bool Boat::containsPoint(Coordinate coor) {
	for (Coordinate point : this->coordinatesArray) {
		if (point.col == coor.col && point.row == coor.row && point.depth == coor.depth) {
			return true;
		}
	}
	return false;
}

bool Boat::equals(std::shared_ptr<Boat> boat) {
	if (this->player != boat->player || this->boatSize != boat->boatSize 
		|| this->coordinatesArray.size() != boat->coordinatesArray.size()) {
		return false;
	}
	for (Coordinate coor : this->coordinatesArray) {
		if (!boat->containsPoint(coor)) {
			return false;
		}
	}
	return true;
}

std::shared_ptr<Boat> Boat::getNewCopy() {
	std::shared_ptr<Boat> copyBoat = std::make_shared<Boat>();
	copyBoat->boatSize = this->boatSize;
	copyBoat->acctualSize = this->acctualSize;
	copyBoat->player = this->player;
	copyBoat->value = this->value;
	copyBoat->coordinatesArray = this->coordinatesArray;

	return copyBoat;
}