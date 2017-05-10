#pragma once

#include "CommonPlayer.h"
#include "IBattleShipGameAlgo.h"

class Point;

class Boat {
	int boatSize;
	int direction; //0 for undecided, 1 for vertical, 2 for horizontal
	int acctualSize;
	int player;
	int hit;
	int value;
	CommonPlayer* owner;
	CommonPlayer* rival;
	std::vector<Point*> pointsArray;
	bool validity;

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
	int getDirection();
	int getPlayer();
	int getAcctualSize();
	int getBoatSize();
	bool isSunk();
	void addHit();
	void addPoint(Point* point);
	void setDirection(int direction);
	bool isValid();
	void setValidity(bool validity);

	Boat(const Boat&) = delete;
	Boat& operator=(const Boat&) = delete;

};