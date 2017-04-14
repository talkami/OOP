#pragma once

#include "IBattleShipGameAlgo.h"
#include "Boat.h"

//includes
class Point {
	int x;
	int y;
	Boat* boat;
	bool near;
	Point* up;
	Point* down;
	Point* left;
	Point* right;
	bool hit;

public:
	Point();
	//never used constructor
	//Point(int x, int y, Boat boat = NULL, int near = 0, Point* up= NULL, Point* down= NULL, Point* left = NULL, Point* right= NULL);
	AttackResult attack();
	~Point();

	bool getNear();
	void setNear(bool near);
	Point* getUp();
	void setUp(Point* point);
	Point* getDown();
	void setDown(Point* point);
	Point* getLeft();
	void setLeft(Point* point);
	Point* getRight();
	void setRight(Point* point);
	Boat* getBoat();
	void setBoat(Boat* boat);
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
};