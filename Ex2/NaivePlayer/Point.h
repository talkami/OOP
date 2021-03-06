#pragma once

#include "IBattleShipGameAlgo.h"
#include "Boat.h"

//includes
class Point {
	int row;
	int col;
	Boat* boat;
	Point* up;
	Point* down;
	Point* left;
	Point* right;
	bool adjacent;
	bool hit;
	bool validAttack;

public:
	Point();
	Point(int r, int c);
	~Point();
	AttackResult attack(int attacker, bool* selfHit);


	bool getNear();
	void setNear(bool adjacent);
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
	int getRow();
	void setRow(int row);
	int getCol();
	void setCol(int col);
	bool isValidAttack();
	void setInvalidAttack();

	Point(const Point&) = delete;
	Point& operator=(const Point&) = delete;

};