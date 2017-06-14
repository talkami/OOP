#pragma once

#include "IBattleShipGameAlgo.h"
#include <vector>

class PlayerBoard;

class Boat {
	int boatSize;
	int direction; //0 for undecided, 1 for vertical, 2 for horizontal 3 for depth direction
	int acctualSize;
	int player;
	int hits;
	int value;
	PlayerBoard* ownerBoard;
	PlayerBoard* rivelBoard;
	std::vector<Coordinate> coordinatesArray;
	bool validity;

	void notifyPlayerSunk();
	void notifyPlayerCreated();
	int setValue(int size);


public:
	Boat() {}
	Boat(int size, int player, PlayerBoard* ownerBoard, PlayerBoard* rivelBoard, Coordinate* firstPoint);
	~Boat();
	void notifyBoardSunk();
	int getNumOftHits();
	int getDirection();
	int getPlayer();
	int getBoatSize();
	int getAcctualSize();
	PlayerBoard* getOwnerBoard();
	PlayerBoard* getRivalBoard();
	bool isSunk();
	bool isValid();
	void addPoint(Coordinate point);
	void setDirection(int direction);
	void setValidity(bool validity);
	void mergeBoats(shared_ptr<Boat> boat);
	std::vector<std::tuple<int, int,int>> getPoints();
	std::vector<Coordinate> getCoordinatesArray();
	int getValue ();
	int addHit(Coordinate coor);

	Boat(const Boat&) = delete;
	Boat& operator=(const Boat&) = delete;

};