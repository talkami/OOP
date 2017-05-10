#include "Point.h"
#include <iostream>

Point::Point() :
	row(-1), col(-1), boat(nullptr), adjacent(false), up(nullptr),
	down(nullptr), left(nullptr), right(nullptr), hit(false), validAttack(true) {
}

Point::~Point() {
}

// do the attack on this point
AttackResult Point::attack(int attacker, bool* selfHit) {
	if (this->boat == nullptr) {
		return AttackResult::Miss;
	}
	else {
		if (this->boat->getPlayer() == attacker) {
			*selfHit = true;
		}
		if (!hit) {
			this->boat->addHit();
			this->hit = true;
			if (!boat->isSunk()) {
				return AttackResult::Hit;
			}
			else {
				return AttackResult::Sink;
			}
		}
		else {
			// the attack was successful but this point is already hurt
			//if the boat has sunk than it's miss
			if (!boat->isSunk()) {
				return AttackResult::Hit;
			}
			else {
				return AttackResult::Miss;
			}
		}
	}

}

//getters
Boat* Point::getBoat() {
	return this->boat;
}
bool Point::getNear() {
	return this->adjacent;
}
Point* Point::getUp() {
	return this->up;
}
Point* Point::getDown() {
	return this->down;
}
Point* Point::getLeft() {
	return this->left;
}
Point* Point::getRight() {
	return this->right;
}
int Point::getRow() {
	return this->row;
}
int Point::getCol() {
	return this->col;
}
bool Point :: isValidAttack (){
	return this -> validAttack;
}
//setters
void Point::setBoat(Boat* boat) {
	this->boat = boat;
	this->setInvalidAttack();
	if (this->getUp()) {
		this->getUp()->setNear(true);
	}
	if (this->getLeft()) {
		this->getLeft()->setNear(true);
	}
	if (this->getDown()) {
		this->getDown()->setNear(true);
	}
	if (this->getRight()) {
		this->getRight()->setNear(true);
	}
}

void Point::setNear(bool near) {
	this->adjacent = near;
}
void Point::setUp(Point* Up) {
	this->up = Up;
}
void Point::setDown(Point* Down) {
	this->down = Down;
}
void Point::setLeft(Point* Left) {
	this->left = Left;
}
void Point::setRight(Point* Right) {
	this->right = Right;
}
void Point::setRow(int row) {
	this->row = row;
}
void Point::setCol(int col) {
	this->col = col;
}
void Point:: setInvalidAttack (){
	this-> validAttack = false;
}
