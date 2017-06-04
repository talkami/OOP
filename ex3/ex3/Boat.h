#pragma once

#include "IBattleShipGameAlgo.h"
#include <vector>

class Point;

class Boat {
	int boatSize;
	int direction; //0 for undecided, 1 for vertical, 2 for horizontal 3 for depth direction
	int acctualSize;
	int player;
	int hits;
	int value;
	PlayerBoard* ownerBoard;
	PlayerBoard* rivelBoard;
	std::vector<Coordinate*> coordinatesArray;
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
	void addHit();
	void addPoint(Coordinate* point);
	void setDirection(int direction);
	void setValidity(bool validity);
	void mergeBoats(Boat* boat);
	std::vector<std::pair<int, int,int>> getPoints();


	//new func 
	int getValue ();

	Boat(const Boat&) = delete;
	Boat& operator=(const Boat&) = delete;

};