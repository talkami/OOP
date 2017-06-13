#pragma once
#include "IBattleshipGameAlgo.h"
#include "Boat.h"

class PlayerBoard : public BoardData{
	int _rows = 0;
	int _cols = 0;
	int _depth = 0; 

	int [4] boatsCount = {0};
	std::vector<std::vector<std::vector<char>>> _board;
	std::vector<Boat*> boats;
	int _player; 
	int numOfPlayerBoats;

	//what is it?
	void invalidatePoint(Coordinate c);
public:

	PlayerBoard(int rows, int cols, int depth) : _rows(rows), _cols(cols), _depth(depth) {}
	PlayerBoard(int rows, int cols, int depth, std::vector<std::vector<std::vector<char>>> board, int player) :
		_rows(rows), _cols(cols), _depth(depth), _board(board), _player(player) {}

	virtual char charAt(Coordinate c) const override;
	void addBoat(Boat * boat);
	Boat* getBoatAt (int row, int col, int depth);
	void removeBoat(Boat* boat);
	bool isThereMoreBoats ();
	void editBoardAtPoint (int rows, int cols, int depth, char characterAtPoint);
	bool loadBoard (const BoardData& board);
	std::pair<AttackResult,int> attack (Coordinate coor);
	int* getBoatsCount();
	bool isValidToExplorationAttack(Coordinate coor);
	void invalidateExplorationAttackArea(int row, int col, int depth, int smalestBoat);
	bool isValidAttack (Coordinate coor);
	void setInvalidAttack (Coordinate coor);
	void setInvalidArea (Coordinate coor);
	//ask tal
	void setInvalidHorizontal ();
};