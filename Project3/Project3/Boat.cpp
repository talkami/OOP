#include "Boat.h"
#include "Point.h"
#include <iostream>

//constructor
Boat::Boat(int size, int player, CommonPlayer* PlayerPointer, CommonPlayer* RivalPointer, Point* firstPoint) :
	boatSize(size),
	direction(0),
	acctualSize(1),
	hits(0),
	player(player),
	owner(PlayerPointer),
	rival(RivalPointer),
	validity(true)
{
	this->pointsArray.push_back(firstPoint);
	this->value = setValue(size);
	if (rival != nullptr) {
		notifyPlayerCreated();
	}
}

Boat::~Boat() {
	for (size_t i = 0; i < pointsArray.size(); i++) {
		this->pointsArray[i]->setBoat(nullptr);
	}
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
CommonPlayer* Boat::getOwner() {
	return this->owner;
}
CommonPlayer* Boat::getRival() {
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
bool Boat::isValid() {
	return this->validity;
}

//setters
void Boat::addHit() {
	this->hits++;
	if (this->hits >= this->boatSize) {
		notifyPlayerSunk();
	}
}

void Boat::addPoint(Point* point) {
	this->pointsArray.push_back(point);
	this->acctualSize++;
}

void Boat::setDirection(int direction) {
	this->direction = direction;
}

void Boat::setValidity(bool validity) {
	this->validity = validity;
}

void Boat::mergeBoats(Boat* boat) {
	std::vector<Point*> otherPoints = boat->pointsArray;
	this->acctualSize += boat->acctualSize;
	delete boat;
	for (size_t i = 0; i < otherPoints.size(); i++) {
		otherPoints[i]->setBoat(this);
		this->pointsArray.push_back(otherPoints[i]);
	}
	owner->removeBoat();
}

//private
void Boat::notifyPlayerSunk() {
	owner->removeBoat();
	rival->increaseScore(this->value);
}
void Boat::notifyPlayerCreated() {
	owner->addBoat();
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
		std::cout << "Error! illegal boat!" << std::endl;
		return -1;
	}
}

std::vector<std::pair<int, int>> Boat::getPoints() {
	int size = this->acctualSize;
	std::vector<std::pair<int, int>> arr;
	for (int i = size; i > 0; i--) {
		std::pair<int, int> point(this->pointsArray[i - 1]->getRow(), this->pointsArray[i - 1]->getCol());
		arr.push_back(point);
	}
	std::cout << std::endl;
	return arr;
}