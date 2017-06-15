#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Logger.h"
#include "IBattleshipGameAlgo.h"
#include "PlayerBoard.h"
#include "Boat.h"

class gameBoard {
	std::vector<std::shared_ptr<Boat>> playerAboats;
	std::vector<std::shared_ptr<Boat>>  playerBboats;
	int playerAScore;
	int playerBScore;
	void handleSunkBoat(int owner, int value);

public:
	gameBoard(std::vector<std::shared_ptr<Boat>> boats);
	int getGameScore(int player);
	bool hasNoMoreBoats(int player);
	AttackResult attack(Coordinate coor, int attacker, bool* selfHit);
};


gameBoard