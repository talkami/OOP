#include "SingleGame.h"

//single game constructor
SingleGame::SingleGame(std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>,
	std::shared_ptr<Board>> gameStats) : scoreA(0), scoreB(0), dataA(std::get<0>(gameStats)), 
	dataB(std::get<1>(gameStats)), gameBoard(std::get<2>(gameStats)) {
	this->PlayerA = this->dataA->getDLLAlgo();
	this->PlayerB = this->dataB->getDLLAlgo();
	this->PlayerA->setPlayer(0);
	this->PlayerB->setPlayer(1);
	this->PlayerA->setBoard(this->gameBoard->getPlayerBoard(0));
	this->PlayerB->setBoard(this->gameBoard->getPlayerBoard(1));
}

//single game destructor
SingleGame::~SingleGame() {
	//TBD
}

//init board ask tal
bool SingleGame::setupBoard(std::shared_ptr<Board> board) {

	this->board = &board;
	return true;
}



std::pair<int,int> SingleGame::playSingleGame() {

	while (this->turn >= 0) {
		std::pair<int, int, int> nextMove;
		AttackResult res;
		if (this->turn == 0) {
			nextMove = this->A->attack();
		}
		else if (this->turn == 1) {
			nextMove = this->B->attack();
		}
		else {
			std::cout << "Error! next turn set to an illegal player" << std::endl;
			return false;
		}if (nextMove->getRow == -1 || nextMove->getCol == -1 ||nextMove.depth == -1) {
			if (turn == 0) {
			// how do we define finished attacking?
				this->AFinishedAttacking = true;
			}
			else if (turn == 1){
			// how do we define finished attacking?
				this->BFinishedAttacking = true;
			}
			if (!(this->setNextTurn(AttackResult::Miss, false))) {
				return false;
			}
		}
		bool selfHit = false;

		//create this function at board.h
		res = this->board->play_attack(nextMove, this->turn, &selfHit);
		//check the sig of notifyOnAttackResult
		this->A->notifyOnAttackResult(turn, nextMove.first, nextMove.second,nextMove.third, res);
		this->B->notifyOnAttackResult(turn, nextMove.first, nextMove.second,nextMove.third, res);
		
		//delete? ask tal!!!!!!!!!!!!!!!
		if (this->displayGame && nextMove->getRow != -1 && nextMove->getCol != -1) {
			this->gameBoard.displayAttack(res, nextMove.first, nextMove.second, this->delay);
		}
		if (!(this->setNextTurn(res, selfHit))) {
			return false;
		}
	}

	int AGames = this->dataA->addData(this->winner == 0, this->winner == 1, this->scoreA, this->scoreB);
	int BGames = this->dataB->addData(this->winner == 1, this->winner == 0, this->scoreB, this->scoreA);

	return std::make_pair(AGames, BGames);
}

bool SingleGame::setNextTurn(AttackResult res, bool selfHit) {
	//check for victory
	if (this->board->hasNoMoreBoats(0)) {
		//player A is out of boats - player B wins
		this->winner = 1;
		this->turn = -1;
		return true;
	}
	else if (this->board->hasNoMoreBoats(1)) {
		//player B is out of boats - player A wins
		this->winner = 0;
		this->turn = -1;
		return true;
	}

	//check if one or both playes have finished attacking
	if (this->AFinishedAttacking) {
		if (this->BFinishedAttacking) {
			//both players have finished attacking - end the game
			this->winner = -1;
			this->turn = -2;
			return true;
		}
		else {
			//player A has finished attacking, player B still has moves

			this->turn = 1;
			return true;
		}
	}
	else if (this->BFinishedAttacking) {
		//player B has finished attacking, player A still has moves

		this->turn = 0;
		return true;
	}
	else {
		//both players still have moves to make, determine next move based on last attack result
		if ((res == AttackResult::Miss) || selfHit) {
			//player missed or attacked itself - switch turns 
			this->turn = (this->turn + 1) % 2;
			return true;
		}
		else if (res == AttackResult::Hit || res == AttackResult::Sink) {
			//player hit a rival boat - gets another turn
			return true;
		}
		else {
			std::cout << "Error! undefined attack result given" << std::endl;
			return false;
		}
	}
}