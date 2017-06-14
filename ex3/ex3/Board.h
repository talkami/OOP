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
    int numOfRows, numOfCols, depth;
	PlayerBoard playerABoard;
	PlayerBoard playerBBoard;
	Logger* logger;
	bool errorArray[8] = {false};
	bool hasAdjacentBoats = false;
	int playerAScore;
	int playerBScore;
	Boat** PlayerABoats;
	Boat** PlayerBBoats;

	bool setUpParameters(std::string params);

	void addToPlayerBoard(char currentChar, Coordinate coor);
	void addBoatToBoard(Coordinate coor, int size, int player, std::shared_ptr<PlayerBoard> ownerBoard, std::shared_ptr<PlayerBoard> rivalBoard);
	void checkAdjacentBoat(std::shared_ptr<Boat> boat, Coordinate coor, int size, int direction, int player, std::shared_ptr<PlayerBoard> ownerBoard, std::shared_ptr<PlayerBoard> rivalBoard);
	void checkBoatValidity();
	void mergeBoats(std::shared_ptr<Boat> boat1, std::shared_ptr<Boat> boat2, int direction, std::shared_ptr<PlayerBoard> ownerBoard);
	bool checkBoard();
	bool thereIsABoatNearby(Coordinate coor);
	//should write!!
	void handleSunkBoat (int owner, int value);

public:

	Board() : numOfRows(0), numOfCols(0), depth(0){}
    ~Board ();

	bool loadBoard(const std::string& boardFile, Logger* logger);
	AttackResult attack(Coordinate coor, int attacker, bool* selfHit);
	bool hasNoMoreBoats(int player);
	BoardData& getPlayerBoard (int player);
	int getGameScore(int player);

};