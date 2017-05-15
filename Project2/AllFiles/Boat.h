#pragma once

#include "IBattleShipGameAlgo.h"
#include <vector>

class Point;

class Boat {
	int boatSize;
	int direction; //0 for undecided, 1 for vertical, 2 for horizontal
	int acctualSize;
	int player;
	int hits;
	int value;
	IBattleshipGameAlgo* owner;
	IBattleshipGameAlgo* rival;
	std::vector<Point*> pointsArray;
	bool validity;

	void notifyPlayerSunk();
	void notifyPlayerCreated();
	int setValue(int size);


public:
	Boat() {}
	Boat(int size, int player, IBattleshipGameAlgo* PlayerPointer, IBattleshipGameAlgo* RivalPointer, Point* firstPoint);
	~Boat();

	int getNumOftHits();
	int getDirection();
	int getPlayer();
	int getBoatSize();
	int getAcctualSize();
	IBattleshipGameAlgo* getOwner();
	IBattleshipGameAlgo* getRival();
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