#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Logger.h"
#include "IBattleshipGameAlgo.h"
#include "PlayerBoard.h"
#include "Boat.h"

class Board {
	std::vector<std::vector<std::vector<char>>> board;
    int row, col, depth;
	std::shared_ptr<BoardData> playerABoard;
	std::shared_ptr<BoardData> playerBBoard;
	Logger* logger;
	bool errorArray[9] = {false};
	int playerAScore;
	int playerBScore;
	Boat** PlayerABoats;
	Boat** PlayerBBoats;

	bool setUpParameters(std::string params);

	void addToPlayerBoard(char currentChar, int row, int col, int depth);
	void addBoatToBoard(int row, int col, int depth, int size, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard);
	void checkAdjacentBoat(Boat* boat, int row, int col, int depth, int size, int direction, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard);
	void checkBoatValidity();
	void mergeBoats(Boat* boat1, Boat* boat2, int direction, PlayerBoard* ownerBoard);
	bool checkBoard();
	bool thereIsBoatNearby(int row, int col, int depth);
	//shoud write!!
	void handleSunkBoat (int owner, int value);

public:

	Board() : row(0), col(0), depth(0){}
    ~Board ();

	bool loadBoard(const std::string& boardFile, Logger* logger);
	AttackResult attack (Coordinate coor, int attacker, bool* selfHit);
	bool hasNoMoreBoats (int player);
	BoardData& getPlayerBoard (int player);
	int getGameScore(int player);


};