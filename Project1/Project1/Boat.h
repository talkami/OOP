#pragma once

#include "Player.h"
#include "Point.h"
#include "IBattleShipGameAlgo.h"
class Boat {
	int boatSize;
	int horizontal;
	int acctualSize;
	int player;
	int hit;
	Player* owner;
	int value;
	Player* rival;

	void notifyPlayerSunk();
	void notifyPlayerCreated();
	int setValue(int size);

public:
	Boat(int size, int player, Player* PlayerPointer, Player* rival);
	~Boat();

	int getHit();
	int getHorizontal();
	int getPlayer();
	int getAcctualSize();
	int getBoatSize();
	bool isSunk();
	void setHit(int hitPoints);
	void addPoint();
	void setHorizontal(int horizontal);
};