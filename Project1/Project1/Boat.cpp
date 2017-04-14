#include "Boat.h"
#include <iostream>

//constructor
Boat::Boat(int size, int player, Player* PlayerPointer, Player* rival) {
	this->boatSize = size;
	this->player = player;
	this->acctualSize = 1;
	this->horizontal = 0;
	this->hit = 0;
	this->owner = PlayerPointer;
	this->rival = rival;
	this->value = setValue(size);
	notifyPlayerCreated();
}

Boat::Boat() {
	std::cout << "in Boat constructor, about to create a new boat." << std::endl;
}

Boat::~Boat() {
	std::cout << "in Boat destructor, about to delete a boat." << std::endl;
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
bool Boat::isSunk() {
	if (hit == boatSize) {
		return true;
	}
	else {
		return false;
	}
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
void Boat::addPoint() {
	this->acctualSize = acctualSize + 1;
}
void Boat::setHorizontal(int horizontal) {
	this->horizontal = horizontal;
}


//private
void Boat::notifyPlayerSunk() {
	owner->removeBoat();
	rival->increaseScore(this->value);
}
void Boat::notifyPlayerCreated() {
	owner->addBoat();
}
int setValue(int size) {
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
}