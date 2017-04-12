#pragma once

#include "Player.h"

class Boat {
	int size;
	int horizontal;
	int pointsNum;
	int player;
	int hit;
	Player* PlayerPointer;
};
public:
	Boat(int size, int player, Player* PlayerPointer);
	~Boat();
	int getHorizontal;
	int getPlayer();
	int getPointNum();
	int getSize();
	int isSunk();
	void setHit(int hitPoints);
	void addPoint();
	void setHorizontal(int horizontal);

private:
	void notifyPlayerSunk();
	void notifyPlayerCreated();

};
