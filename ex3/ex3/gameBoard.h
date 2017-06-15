#pragma once
#include <vector>
#include <memory>
#include "IBattleshipGameAlgo.h"
#include "Boat.h"

class GameBoard {
	int rows, cols, depth;
	std::vector<std::shared_ptr<Boat>> playerABoats;
	std::vector<std::shared_ptr<Boat>> playerBBoats;
	int scores[2] = { 0, 0 };
	
	AttackResult checkABoats(Coordinate coor, int attacker, bool* selfHit);
	AttackResult checkBBoats(Coordinate coor, int attacker, bool* selfHit);

public:
	~GameBoard() {}
	GameBoard(int _rows, int _cols, int _depth, std::vector<std::shared_ptr<Boat>> boats);
	int getGameScore(int player);
	bool AIsOutOfBoats();
	bool BIsOutOfBoats();
	AttackResult attack(Coordinate coor, int attacker, bool* selfHit);
};
