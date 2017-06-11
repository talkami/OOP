#pragma once
#include <string>
#include <vector>
#include "Logger.h"
#include "IBattleshipGameAlgo.h"
#include "PlayerBoard.h"
#include "Boat.h"

class Board {
	std::vector<std::vector<std::vector <char> > > board;
    int row, col, depth;
	BoardData* playerABoard;
	BoardData* playerBBoard;
	Logger* logger;
	bool errorArray[9] = {false};

	void addToPlayerBoard(char currentChar, int row, int col, int depth);
	void addBoatToBoard(int row, int col, int depth, int size, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard);
	bool thereIsBoatNearby(int row, int col, int depth);
	void checkAdjacentBoat(Boat* boat, int row, int col, int depth, int size, int direction, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard);
	void checkBoatValidity();
	void mergeBoats(Boat* boat1, Boat* boat2, int direction, PlayerBoard* ownerBoard);
	bool checkBoard();

public:

	Board() : row(0), col(0), depth(0){}
    ~Board ();

	bool loadBoard(const std::string& boardFile, Logger* logger);
	PlayerBoard getPlayerBoard (int player);
};