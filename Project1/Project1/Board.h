#pragma once


#include "Boat.h"
#include "Point.h"
#include <string>
#include <utility> // for std::pair

class Board {
	Point* matrix[10][10];


	int setBoardsToPoint(Point* point, int i, int j, int size, int player, Player* A, Player* B);
	char ** sendBoardToPlayer(Player* X);
public:

	void loadBoard(const std::string& boardFile, Player* A, Player* B);
	Board();
	~Board();
	AttackResult play_attack(std::pair <int, int> attack);

	//unused constructor
	//Board(const string& boardFile);

};

