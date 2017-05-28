#pragma once
#include "IBattleshipGameAlgo.h"

class Player : IBattleshipGameAlgo{
	int player;
	BoardData* board;

	Coordinate findNextAttack();

public:
	virtual void setPlayer(int player);
	virtual void setBoard(const BoardData& board);	
	virtual Coordinate attack();
	virtual void notifyOnAttackResult(int player, Coordinate move, AttackResult result);

};