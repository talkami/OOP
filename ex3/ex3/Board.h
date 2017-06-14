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
	bool errorArray[8] = {false};
	bool hasAdjacentBoats = false;
	std::vector<std::shared_ptr<Boat>> boats;

	bool setUpParameters(std::string params);
	void addBoatToBoard(Coordinate coor, int size, int player);
	std::shared_ptr<Boat> getBoatAt(Coordinate coor);
	void checkAdjacentBoat(std::shared_ptr<Boat> boat, Coordinate coor, int size, int direction, int player);
	void addToPlayerBoard(char currentChar, Coordinate coor);
	void checkBoatValidity();
	void mergeBoats(std::shared_ptr<Boat> boat1, std::shared_ptr<Boat> boat2, int direction);
	bool checkBoard(Logger* logger);
	bool isThereABoatNearby(Coordinate coor);
	void deleteBoat(std::shared_ptr<Boat> boat);

public:

	Board() : numOfRows(0), numOfCols(0), depth(0){}
    ~Board(){}
	Board(const Board&) = delete;
	Board(const Board&&) = delete;
	Board& operator=(const Board& board) = delete;

	bool loadBoard(const std::string& boardFile, Logger* logger);
	BoardData& getPlayerBoard (int player);

};