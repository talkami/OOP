#pragma once
#include "IBattleshipGameAlgo.h"

class PlayerBoard : BoardData{
	int _rows = 0;
	int _cols = 0;
	int _depth = 0; 

	//new fields
	vector<vector<vector <char> > > _board;
	std::vector<Boat*> boats;
	int _player; 
	int numOfPlayerBoats;

	//what is it?
	void invalidatePoint(Coordinate c);
public:

	PlayerBoard(int rows, int cols, int depth) : _rows(rows), _cols(cols), _depth(depth) {}
	virtual char charAt(Coordinate c) const;

	//new funcs

	void addBoat(Boat * boat);
	PlayerBoard (int rows, int cols, int depth, vector<vector<vector <char> > > board, int player): _rows(rows), _cols(cols), _depth(depth), _board(board), _player (player){}
	Boat* getBoatAt (int row, int col, int depth);
	void removeBoat(Boat* boat);
	bool isThereMoreBoats ();
	void editBoardAtPoint (int rows, int cols, int depth, char characterAtPoint);

};