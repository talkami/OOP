#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

#include "Player.h"
#include "Board.h"

class Game {
	Player A;
	Player B;
	Board game_board;
	int turn;
public:
	//core functions
	Game();
	~Game();
	int initGame(const string adrress);
	int playGame();
	

	//getters if need

	//setters if need

private:
	void setNextTurn(AttackResult result);
	void endGame();
};
#endif