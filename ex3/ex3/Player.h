#pragma once
#include "IBattleshipGameAlgo.h"
#include "PlayerBoard.h"

#include <list>
#include <map>
#include <memory>

class Player : public IBattleshipGameAlgo{
	int playerNum;
	std::unique_ptr<PlayerBoard> player_board;
	bool finishedAttacking;
	int attackDir; // 0 undecided, 1 horizontal, 2 vertical, 3 depth 
	std::list<Coordinate> goodShots;
	std::vector<Coordinate> possibleAttacks;
	Coordinate lastHit = Coordinate(-1, -1, -1);

	void setAttackArea(int row, int col, int depth);	
	Coordinate findGoodAttack();

public:
	virtual void setPlayer(int player) override;
	virtual void setBoard(const BoardData& board)override;	
	virtual Coordinate attack()override;
	virtual void notifyOnAttackResult(int player, Coordinate move, AttackResult result)override;

	Player() : finishedAttacking(false) {}
	~Player() {}
};

static std::vector<Player*> _instancesVec; //Our Player collection