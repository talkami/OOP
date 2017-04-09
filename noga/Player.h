#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

#include "Board.h"
#include "Boat.h"

class Player: public IBattleshipGameAlgo {
	Boat boats[5];
	int score;
	Board board;
};

#endif
