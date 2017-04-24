#pragma once
#include "IBattleshipGameAlgo.h"

#include <vector>
#include <utility> 

class Player: public IBattleshipGameAlgo {
	char player_board[10][10];
	int gameScore;
	int totalScore;
	int wins;
	std::vector<std::pair<int, int>> attackMoves;
	int attackNumber;
	size_t maxMoves;
	int numOfBoats;

public:
	Player();
	~Player();
	virtual void setBoard(int player, const char** board, int numRows, int numCols) override;
	virtual bool init(const std::string& path) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override; 
	void getMoves(const std::string& attackFile);
	void processLine(const std::string& line);
	static std::vector<std::string> split(const std::string &s, char delim);
	bool hasFinishedAttacking();
	bool hasNoMoreBoats();
	void addBoat();
	void removeBoat();
	int getNumOfBoats();
	int getGameScore();
	void addWin();
	void increaseScore(int amount);

	Player(const Player&) {}
	Player& operator=(const Player&) {}

};
