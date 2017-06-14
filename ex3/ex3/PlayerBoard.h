#pragma once
#include "IBattleshipGameAlgo.h"
#include "Boat.h"
#include <memory>

class PlayerBoard : public BoardData{
	int boatsCount[4] = {0};
	std::vector<std::vector<std::vector<char>>> board;
	int playerNum; 

	//what is it?
	void invalidatePoint(Coordinate c);

	bool invalidCoordinate(Coordinate c) const;

public:
	PlayerBoard(){}
	~PlayerBoard(){}
	PlayerBoard(const PlayerBoard&) = delete;
	PlayerBoard(const PlayerBoard&&) = delete;
	PlayerBoard& operator=(const PlayerBoard& board) = delete;

	void setVars(int rows, int cols, int depth, int player);
	void loadBoard(const BoardData& boardData, int player);


	virtual char charAt(Coordinate c) const override;
	void editBoardAtPoint (Coordinate coor, char characterAtPoint);
	bool isValidToExplorationAttack(Coordinate coor);
	void invalidateExplorationAttackArea(Coordinate c, int smalestBoat);
	void setChar(Coordinate coor, char ch);

	void setInvalidVertical(Coordinate coor) ;
	void setInvalidDepth(Coordinate coor) ;
	bool isValidAttack (Coordinate coor);
	void setInvalidAttack (Coordinate coor);
	void setInvalidArea (Coordinate coor);
	void setInvalidHorizontal(Coordinate coor);

};