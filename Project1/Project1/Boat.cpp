#include "Boat.h"
#include "Point.h"


//constructor
Boat::Boat(int size, int player, Player* PlayerPointer, Player* rival, Point* firstPoint) {
	std::cout << "in Boat constructor, about to create a new boat. at (" << firstPoint->getX() << "," << firstPoint->getY() << ")"<< std::endl;
	this->boatSize = size;
	this->player = player;
	this->acctualSize = 1;
	this->horizontal = 0;
	this->hit = 0;
	this->owner = PlayerPointer;
	this->rival = rival;
	this->value = setValue(size);
	this->valid = true;
	this->pointsArray[0] = firstPoint;
	notifyPlayerCreated();
}

Boat::Boat() {
	std::cout << "in Boat empty constructor, about to create a new boat." << std::endl;
}

Boat::~Boat() {
	std::cout << "in Boat destructor, about to delete a boat." << std::endl;
	for (int i = 0; i < this->acctualSize; i++) {
		this->pointsArray[i]->setBoat(nullptr);
	}
}

//getters
int Boat::getHorizontal() {
	return this->horizontal;
}

int Boat::getPlayer() {
	return this->player;
}
int Boat::getAcctualSize() {
	return this->acctualSize;
}
int Boat::getBoatSize() {
	return this->boatSize;
}
int Boat::getHit() {
	return this->hit;
}
Player* Boat::getOwner() {
	return this->owner;
}
bool Boat::isSunk() {
	if (hit == boatSize) {
		return true;
	}
	else {
		return false;
	}
}

bool Boat::isValid() {
	return this->valid;
}
//setters
void Boat::setHit(int hitPoints) {
	this->hit = hitPoints;
	if (this->hit >= this->boatSize) {
		notifyPlayerSunk();
	}
	// update the players points
	//update the player
}
void Boat::addPoint(Point* point) {
	std::cout << "adding point to boat at i=" << point->getX() << ", j=" << point->getY() << std::endl;
	this->pointsArray[this->acctualSize] = point;
	this->acctualSize = acctualSize + 1;
}
void Boat::setHorizontal(int horizontal) {
	this->horizontal = horizontal;
}
void Boat::setValid(bool valid) {
	this->valid = valid;
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
		std::cout << "illegal boat!" << std::endl;
		return -1;
	}
}