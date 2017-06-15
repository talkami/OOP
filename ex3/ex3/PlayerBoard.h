#pragma once
#include "IBattleshipGameAlgo.h"
#include "Boat.h"
#include <memory>

class PlayerBoard : public BoardData{
	std::vector<std::vector<std::vector<char>>> board;
	int playerNum; 

	bool invalidCoordinate(Coordinate c) const;

public:
	PlayerBoard() {}
	~PlayerBoard() {}
	PlayerBoard(const PlayerBoard&) = delete;
	PlayerBoard(const PlayerBoard&&) = delete;
	PlayerBoard& operator=(const PlayerBoard& board) = delete;

	virtual char charAt(Coordinate c) const override;

	void setVars(int rows, int cols, int depth, int player);
	void loadBoard(const BoardData& boardData, int player);
	void editBoardAtPoint(Coordinate coor, char characterAtPoint);
	bool isValidAttack(Coordinate coor);
	void setInvalidVertical(Coordinate coor);
	void setInvalidDepth(Coordinate coor);
	void setInvalidAttack(Coordinate coor);
	void setInvalidArea(Coordinate coor);
	void setInvalidHorizontal(Coordinate coor);

};