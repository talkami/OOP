#pragma once
#include "IBattleshipGameAlgo.h"
#include "PlayerBoard.h"

#include<list>
#include<map>

class Player : public IBattleshipGameAlgo{
	int playerNum;
	PlayerBoard* player_board;
	bool finishedAttacking;
	bool isThereGoodAttack;
	int horizonalGoodAttack; //0 dont know, 1 horizontal, 2 vertical
	int currentAttack; // 0 undecided, 1 vertical, 2 horizontal
	std::list<std::tuple<int, int, int>> goodShots;
	std::tuple<int, int, int> down;
	std::tuple<int, int, int> up;
	std::tuple<int, int, int> left;
	std::tuple<int, int, int> right;
	AttackResult result;
	int numOfDepths = 0;
	int numOfRows = 0;
	int numOfCols = 0;
	int smallestBoat;
	int* boatsCount;
	void setGoodShot(int row, int col, int depth);	
	void handleAttackResult();
	std::vector <Coordinate> possibleAttacks;
	Coordinate playGoodAttack();
	//whats this?
	Coordinate findNextAttack();

public:
	virtual void setPlayer(int player) override;
	virtual void setBoard(const BoardData& board)override;	
	virtual Coordinate attack()override;
	virtual void notifyOnAttackResult(int player, Coordinate move, AttackResult result)override;

	Player();
	~Player();
	//unique func
};

static std::vector<Player*> _instancesVec; //Our Player collection