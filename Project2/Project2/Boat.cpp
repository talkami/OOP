#include "Boat.h"
#include "Point.h"
#include <iostream>

//constructor
Boat::Boat(int size, int player, CommonPlayer* PlayerPointer, CommonPlayer* RivalPointer, Point* firstPoint) : 
	boatSize(size),
	player(player),
	acctualSize(1),
	direction(0),
	hit(0),
	owner(PlayerPointer),
	rival(RivalPointer),
	validity(true)
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
int Boat::getDirection() {
	return this->direction;
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
	return this->validity;
}
//setters
void Boat::addHit() {
	this->hit++;
	if (this->hit >= this->boatSize) {
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