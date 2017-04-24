#pragma once

#include "Player.h"
#include "IBattleShipGameAlgo.h"

class Point;

class Boat {
	int boatSize;
	int horizontal;
	int acctualSize;
	int player;
	int hit;
	Player* owner;
	int value;
	Player* rival;
	Point* pointsArray[10];
	bool valid;

	void notifyPlayerSunk();
	void notifyPlayerCreated();
	int setValue(int size);


public:
	Boat(int size, int player, Player* PlayerPointer, Player* rival, Point* firstPoint);
	Boat();
	~Boat();

	int getHit();
	Player* getOwner();
	int getHorizontal();
	int getPlayer();
	int getAcctualSize();
	int getBoatSize();
	bool isSunk();
	void setHit(int hitPoints);
	void addPoint(Point* point);
	void setHorizontal(int horizontal);
	bool isValid();
	void setValid(bool valid);

	Boat(const Boat&) {}
	Boat& operator=(const Boat&) {}

};