#include "Boat.h"
#include "Point.h"
#include <iostream>

//constructor
Boat::Boat(int size, int player, CommonPlayer* PlayerPointer, CommonPlayer* RivalPointer, Point* firstPoint) : 
	boatSize(size),
	player(player),
	acctualSize(1),
	horizontal(0),
	hit(0),
	owner(PlayerPointer),
	rival(RivalPointer),
	valid(true)
	{	
		this->pointsArray.push_back(firstPoint);
		this->value = setValue(size);
		if (rival != nullptr){
			notifyPlayerCreated();
	}
}

Boat::Boat() {}



Boat::~Boat() {
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
CommonPlayer* Boat::getOwner() {
	return this->owner;
}
CommonPlayer* Boat:: getRival(){
	return this->rival;
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
	this->pointsArray.push_back(point);
	this->acctualSize++;
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
		std::cout << "Error! illegal boat!" << std::endl;
		return -1;
	}
}