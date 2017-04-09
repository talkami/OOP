#include "Game.h"

Point::Point(int x, int y, Boat boat = NULL, int near = 0, Point * up = NULL, Point* down = NULL, Point* left = NULL, Point* right = NULL) :
x(x), y(y), boat(boat), near(near), up(up), down(down), left(left), right(right), hit = 0 {}
Point::Point():
x(-1), y(-1), boat(NULL), near(0), up(NULL), down(NULL), left(NULL), right(NULL), hit = 0{}
AttackResult Point ::attack() {
	if (this.boat == NULL){
		return Miss;
	}
	else {
		if (hit = 0){
			this.boat.setHit(this.boat.getHit + 1);
			this.hit = 1;
			if (boat.isSunk == 0){
				return Hit;
			}
			else{
				// update the points
				return Sink;
			}
		}
		else{
			return Miss;
		}
	}
	
}

//getters
Boat Point::getBoat() {
	return this.boat;
}
int Point::getNear(){
	return this.near;
}
Point* Point::getUp(){
	return this.Up;
}
Point* Point::getDown(){
	return this.Down;
}
Point* Point::getLeft(){
	return this.Left;
}
Point* Point::getRight(){
	return this.Right;
}

//setters
void Point::setBoat(Boat boat){
	this.boat = boat;
}
void Point::setNear(int near){
	this.near = near;
}
void Point::setUp(Point* Up){
	this.Up = Up;
}
void Point::setDown(Point* Down){
	this.Down = Down;
}
void Point::setLeft(Point* Left){
	this.Left = Left;
}
void Point::setRight(Point* Right){
	this.Right = Right;
}