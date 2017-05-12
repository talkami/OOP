#pragma once

#include "CommonPlayer.h"
#include "IBattleShipGameAlgo.h"

class Point;

class Boat {
	int boatSize;
	int direction; //0 for undecided, 1 for vertical, 2 for horizontal
	int acctualSize;
	int player;
	int hits;
	int value;
	CommonPlayer* owner;
	CommonPlayer* rival;
	std::vector<Point*> pointsArray;
	bool validity;

	void notifyPlayerSunk();
	void notifyPlayerCreated();
	int setValue(int size);


public:
	Boat() {}
	Boat(int size, int player, CommonPlayer* PlayerPointer, CommonPlayer* RivalPointer, Point* firstPoint);
	~Boat();

	int getNumOftHits();
	int getDirection();
	int getPlayer();
	int getBoatSize();
	int getAcctualSize();	
	CommonPlayer* getOwner();
	CommonPlayer* getRival();
	bool isSunk();	
	bool isValid();
	void addHit();
	void addPoint(Point* point);
	void setDirection(int direction);
	void setValidity(bool validity);
	void mergeBoats(Boat* boat);
	std::vector<std::pair<int, int>> getPoints();

	Boat(const Boat&) = delete;
	Boat& operator=(const Boat&) = delete;

};