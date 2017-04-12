#include "Point.h"

// never used constructor
//Point::Point(int x, int y, Boat boat = NULL, int near = 0, Point * up = NULL, Point* down = NULL, Point* left = NULL, Point* right = NULL) :
//x(x), y(y), boat(boat), near(near), up(up), down(down), left(left), right(right), hit = 0 {}

// empty constructor
Point::Point() :
	x(-1), y(-1), boat(nullptr), near(false), up(nullptr), down(nullptr), left(nullptr), right(nullptr), hit(false) {}

// do the attack on this point
AttackResult Point::attack() {
	if (this->boat == nullptr) {
		return AttackResult::Miss;
	}
	else {
		if (!hit) {
			this->boat->setHit(this->boat->getHit() + 1);
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
			return AttackResult::Hit;
		}
	}

}

//getters
Boat* Point::getBoat() {
	return this->boat;
}
bool Point::getNear() {
	return this->near;
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
int Point::getX() {
	return this->x;
}
int Point::getY() {
	return this->y;
}
//setters
void Point::setBoat(Boat* boat) {
	this->boat = boat;
}
void Point::setNear(int near) {
	this->near = near;
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
void Point::setX(int x) {
	this->x = x;
}
void Point::setY(int y) {
	this->y = y;
}