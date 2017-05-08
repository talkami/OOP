#pragma once

#include "CommonPlayer.h"
#include "IBattleShipGameAlgo.h"

class Point;

class Boat {
	int boatSize;
	int horizontal;
	int acctualSize;
	int player;
	int hit;
	CommonPlayer* owner;
	int value;
	CommonPlayer* rival;
	std::vector<Point*> pointsArray;
	bool valid;

	void notifyPlayerSunk();
	void notifyPlayerCreated();
	int setValue(int size);


public:
	Boat(int size, int player, CommonPlayer* PlayerPointer, CommonPlayer* rival, Point* firstPoint);
	Boat();


	~Boat();


	int getHit();
	CommonPlayer* getOwner();
	CommonPlayer* getRival();
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