#include "Boat.h"
#include "Point.h"
#include <iostream>

//constructor
Boat(int size, int player, PlayerBoard* ownerBoard, PlayerBoard* rivelBoard, Coordinate* firstPoint) :
	boatSize(size),
	direction(0),
	acctualSize(1),
	hits(0),
	player(player),
	ownerBoard(ownerBoard),
	rivelBoard(rivelBoard),
	validity(true)	
	std::vector<Coordinate*> coordinatesArray;
{
	this->coordinatesArray.push_back(firstPoint);
	this->value = setValue(size);

}

Boat::~Boat() {
//	for (size_t i = 0; i < pointsArray.size(); i++) {
//		this->coordinatesArray[i]->setBoat(nullptr);
//	}
}

//getters
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
PlayerBoard* Boat::getOwnerBoard() {
	return this->owner;
}
PlayerBoard* Boat::getRivalBoard() {
	return this->rival;
}
bool Boat::isSunk() {
	if (hits == boatSize) {
		return true;
	}
	else {
		return false;
	}
}
int Boat :: getValue (){
	return this->value;
}

bool Boat::isValid() {
	return this->validity;
}

//setters
void Boat::addHit() {
	this->hits++;
}

void Boat::addPoint(Coordinate* point) {
	this->coordinatesArray.push_back(point);
	this->acctualSize++;
}

void Boat::setDirection(int direction) {
	this->direction = direction;
}

void Boat::setValidity(bool validity) {
	this->validity = validity;
}

void Boat::mergeBoats(Boat* boat) {
	std::vector<Coordinate*> otherPoints = boat->coordinatesArray;
	this->acctualSize += boat->acctualSize;
	delete boat;
	for (size_t i = 0; i < otherPoints.size(); i++) {
		otherPoints[i]->setBoat(this);
		this->coordinatesArray.push_back(otherPoints[i]);
	}
	
}

//private

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
		std::cout << "Error! illegal boat!" << std::endl;
		return -1;
	}
}

std::vector<std::pair<int, int, int>> Boat::getPoints() {
	int size = this->acctualSize;
	std::vector<std::pair<int, int, int>> arr;
	for (int i = size; i > 0; i--) {
		std::pair<int, int> point(this->coordinatesArray[i - 1]->getRow(), this->coordinatesArray[i - 1]->getCol(), this->coordinatesArray[i - 1]->getDepth());
		arr.push_back(point);
	}
	std::cout << std::endl;
	return arr;
}