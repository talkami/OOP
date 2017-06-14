#pragma once
#include "IBattleshipGameAlgo.h"
#include "Boat.h"
#include <memory>

class PlayerBoard : public BoardData{
	int boatsCount[4] = {0};
	std::vector<std::vector<std::vector<char>>> board;
	std::vector<std::shared_ptr<Boat>> boats;
	int playerNum; 
	int numOfPlayerBoats;

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

	virtual char charAt(Coordinate c) const override;
	void addBoat(std::shared_ptr<Boat> boat);
	std::shared_ptr<Boat> getBoatAt (Coordinate coor);
	void removeBoat(std::shared_ptr<Boat> boat);
	bool isThereMoreBoats ();
	void editBoardAtPoint (Coordinate coor, char characterAtPoint);
	void loadBoard (const BoardData& board);
	std::pair<AttackResult,int> attack (Coordinate coor);
	int* getBoatsCount();
	bool isValidToExplorationAttack(Coordinate coor);
	void invalidateExplorationAttackArea(int row, int col, int depth, int smalestBoat);

	void setInvalidVertical(Coordinate coor) ;
	void setInvalidDepth(Coordinate coor) ;
	bool isValidAttack (Coordinate coor);
	void setInvalidAttack (Coordinate coor);
	void setInvalidArea (Coordinate coor);
	void setInvalidHorizontal(Coordinate coor);

};