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
	Game(Player A, Player B, Board game_board);
	~Game();
	AttackResult play_turn();

private:
	void Game::switchTurn();
	int Game::getTurn()const;
	void endGame();
};
#endif