#pragma once

#include "IBattleShipGameAlgo.h"
#include <vector>
#include <memory>

class PlayerBoard;

class Boat {
	int boatSize;
	int direction; //0 for undecided, 1 for vertical, 2 for horizontal 3 for depth direction
	int acctualSize;
	int player;
	int hits;
	int value;
	std::vector<Coordinate> coordinatesArray;
	bool validity;

	int setValue(int size);

public:
	Boat() : direction(0), hits(0), validity(true) {}
	Boat(int size, int player, Coordinate firstPoint);
	~Boat(){}

	bool containsPoint(Coordinate coor);
	std::shared_ptr<Boat> getNewCopy();
	int getNumOftHits();
	int getDirection();
	int getPlayer();
	int getBoatSize();
	int getAcctualSize();
	bool isSunk();
	bool isValid();
	void addPoint(Coordinate point);
	void setDirection(int direction);
	void setValidity(bool validity);
	void mergeBoats(std::shared_ptr<Boat> boat);
	int getValue();
	int addHit(Coordinate coor);
	bool equals(std::shared_ptr<Boat> boat);

	Boat(const Boat&) = delete;
	Boat(const Boat&&) = delete;
	Boat& operator=(const Boat& boat) = delete;

};