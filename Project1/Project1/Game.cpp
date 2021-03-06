#include "Game.h"

bool Game::initGame(const std::string& path) {
	bool result;
	result = this->getInitFiles(path);
	if (result) {
		result = this->gameBoard.loadBoard(this->boardFileLister.getFilesList()[0], &this->A, &this->B);
		if (result) {
			this->A.getMoves(this->playerAFileLister.getFilesList()[0]);
			this->B.getMoves(this->playerBFileLister.getFilesList()[0]);
			this->turn = 0;
			this->A.setBoard(const_cast<const char**>(this->gameBoard.getPlayerABoard()), 10, 10);
			this->B.setBoard(const_cast<const char**>(this->gameBoard.getPlayerBBoard()), 10, 10);
		}
	}
	return result;
}


bool Game::playGame() {
	while (this->turn >= 0) {
		std::pair<int, int> nextMove;
		AttackResult res;
		if (this->turn == 0) {
			nextMove = this->A.attack();
		}
		else if (this->turn == 1) {
			nextMove = this->B.attack();
		}
		else {
			std::cout << "Error! next turn set to an illegal player" << std::endl;
			return false;
		}if (nextMove.first == -1 || nextMove.second == -1) {
			if (!(this->setNextTurn(AttackResult::Miss, false))) {
				return false;
			}
		}
		bool selfHit = false;
		res = this->gameBoard.play_attack(nextMove, this->turn, &selfHit);
		this->A.notifyOnAttackResult(turn, nextMove.first, nextMove.second, res);
		this->B.notifyOnAttackResult(turn, nextMove.first, nextMove.second, res);
		if (!(this->setNextTurn(res, selfHit))) {
			return false;
		}
	}

	if (!this->endGame()) {
		return false;
	}

	return true;
}


bool Game::getInitFiles(const std::string& path) {
	bool result = true;
	std::string errorPath;
	if (path == ".") {
		errorPath = "Working Directory";
	}
	else {
		errorPath = path;
	}

	this->boardFileLister = SeaBattleBoardLister(path);
	if (this->boardFileLister.getFilesList().size() == 0) {
		std::cout << "Missing board file (*.sboard) looking in path: " << errorPath << std::endl;
		result = false;
	}
	this->playerAFileLister = AttackAFileLister(path);
	if (this->playerAFileLister.getFilesList().size() == 0) {
		std::cout << "Missing attack file for player A (*.attack-a) looking in path: " << errorPath << std::endl;
		result = false;
	}
	this->playerBFileLister = AttackBFileLister(path);
	if (this->playerBFileLister.getFilesList().size() == 0) {
		std::cout << "Missing attack file for player B (*.attack-b) looking in path: " << errorPath << std::endl;
		result = false;
	}
	return result;
}

bool Game::setNextTurn(AttackResult res, bool selfHit) {
	//check for victory
	if (this->A.hasNoMoreBoats()) {
		//player A is out of boats - player B wins
		this->winner = 'B';
		this->B.addWin();
		this->turn = -1;
		return true;
	}
	else if (this->B.hasNoMoreBoats()) {
		//player B is out of boats - player A wins
		this->winner = 'A';
		this->A.addWin();
		this->turn = -1;
		return true;
	}

	//check if one or both playes have finished attacking
	if (this->A.hasFinishedAttacking()) {
		if (this->B.hasFinishedAttacking()) {
			//both players have finished attacking - end the game
			this->turn = -2;
			return true;
		}
		else {
			//player A has finished attacking, player B still has moves
			this->turn = 1;
			return true;
		}
	}
	else if (this->B.hasFinishedAttacking()) {
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

bool Game::endGame() {
	switch (this->turn) {
	case -1:
		std::cout << "Player " << this->winner << " won" << std::endl;
	case -2:
		std::cout << "Points:" << std::endl;
		std::cout << "Player A: " << this->A.getGameScore() << std::endl;
		std::cout << "Player B: " << this->B.getGameScore() << std::endl;
		return true;
	default:
		std::cout << "Error! reached 'endGame' function with invalid 'turn'" << std::endl;
		return false;
	}
}