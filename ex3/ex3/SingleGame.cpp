#include "SingleGame.h"
#include <iostream>

//single game constructor
SingleGame::SingleGame(std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>,
	std::shared_ptr<Board>> gameStats) : dataA(std::get<0>(gameStats)), dataB(std::get<1>(gameStats)) {
	std::cout << "in single game const" << std::endl;
	this->board = std::get<2>(gameStats)->getGameBoard();
	this->PlayerA = this->dataA->getDLLAlgo();
	std::cout << "got player A dll" << std::endl;
	this->PlayerB = this->dataB->getDLLAlgo();
	std::cout << "got player B dll" << std::endl;
	this->PlayerA->setPlayer(0);
	std::cout << "set Player A" << std::endl;
	this->PlayerB->setPlayer(1);
	std::cout << "set Player B" << std::endl;
	this->PlayerA->setBoard(std::get<2>(gameStats)->getPlayerBoard(0));
	std::cout << "setup player A board" << std::endl;
	this->PlayerB->setBoard(std::get<2>(gameStats)->getPlayerBoard(1));
	std::cout << "started a single game" << std::endl;
}

std::pair<int,int> SingleGame::playSingleGame() {
	std::cout << "playing game" << std::endl;

	while (this->turn >= 0) {
		AttackResult res;
		Coordinate nextMove = Coordinate(-1, -1, -1);
		if (this->turn == 0) {
			nextMove = this->PlayerA->attack();
		}
		else if (this->turn == 1) {
			nextMove = this->PlayerB->attack();
		}
		std::cout << "player "<< turn << " is about to attack at: " << nextMove.row << ", " << nextMove.col << ", " << nextMove.depth << std::endl;
		if (nextMove.row == -1 || nextMove.col == -1 ||nextMove.depth == -1) {
			if (turn == 0) {
				this->AFinishedAttacking = true;
			}
			else if (turn == 1){
				this->BFinishedAttacking = true;
			}
			setNextTurn(AttackResult::Miss, false);
		}
		bool selfHit = false;

		res = this->board->attack(nextMove, this->turn, &selfHit);
		std::cout << "Attack result is ";
		if (res == AttackResult::Miss) {
			std::cout << "miss" << std::endl;
		}else if (res == AttackResult::Hit) {
			std::cout << "hit" << std::endl;
		}else if (res == AttackResult::Sink) {
			std::cout << "sink" << std::endl;
		}
		this->PlayerA->notifyOnAttackResult(turn, nextMove, res);
		this->PlayerB->notifyOnAttackResult(turn, nextMove, res);
		
		setNextTurn(res, selfHit);
	}
	int scoreA = this->board->getGameScore(0);
	int scoreB = this->board->getGameScore(1);
	std::cout << "winner is " << winner << std::endl;
	std::cout << "player A score is:  " << scoreA << ", player B score is: " << scoreB << std::endl;
	int AGames = this->dataA->addData(this->winner == 0, this->winner == 1, scoreA, scoreB);
	int BGames = this->dataB->addData(this->winner == 1, this->winner == 0, scoreB, scoreA);

	return std::make_pair(AGames, BGames);
}

void SingleGame::setNextTurn(AttackResult res, bool selfHit) {
	//check for victory
	if (this->board->AIsOutOfBoats()) {
		//player A is out of boats - player B wins
		this->winner = 1;
		this->turn = -1;
		return;
	}
	else if (this->board->BIsOutOfBoats()) {
		//player B is out of boats - player A wins
		this->winner = 0;
		this->turn = -1;
		return;
	}

	//check if one or both playes have finished attacking
	if (this->AFinishedAttacking) {
		if (this->BFinishedAttacking) {
			//both players have finished attacking - end the game
			this->winner = -1;
			this->turn = -1;
		}
		else {
			//player A has finished attacking, player B still has moves
			this->turn = 1;
		}
	}
	else if (this->BFinishedAttacking) {
		//player B has finished attacking, player A still has moves
		this->turn = 0;
	}
	else {
		//both players still have moves to make, determine next move based on last attack result
		if ((res == AttackResult::Miss) || selfHit) {
			//player missed or attacked itself - switch turns 
			this->turn = (this->turn + 1) % 2;
		}
	}
}