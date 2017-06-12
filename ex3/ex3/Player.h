#pragma once
#include "IBattleshipGameAlgo.h"

class Player : IBattleshipGameAlgo{
	int playerNum
	PlayerBoard* player_board;
	int attackRow;
	int attackCol;
	bool finishedAttacking;
	bool isThereGoodAttack;
	int horizonalGoodAttack; //0 dont know, 1 horizontal, 2 vertical
	int currentAttack; // 0 undecided, 1 vertical, 2 horizontal
	std::list<std::pair<int, int, int>> goodShots;
	std::pair<int, int, int> down;
	std::pair<int, int, int> up;
	std::pair<int, int, int>left;
	std::pair<int, int, int> right;
	AttackResult result;

	void setGoodShot(int row, int col, int depth);


	//whats this?
	Coordinate findNextAttack();

public:
	virtual void setPlayer(int player);
	virtual void setBoard(const BoardData& board);	
	virtual Coordinate attack();
	virtual void notifyOnAttackResult(int player, Coordinate move, AttackResult result);

	Player();
	~Player();
	virtual bool init(const std::string& path) override;
	virtual void notifyOnAttackResult(int player, int row, int col, int depth, AttackResult result) override;
	virtual bool hasFinishedAttacking() override;

	Player(const SmartPlayer&) = delete;
	Player& operator=(const SmartPlayer&) = delete;

	//unique func
	void handleAttackResult();
	std::pair <int, int> playGoodAttack();

};