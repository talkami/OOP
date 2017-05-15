#include "Game.h"

Game::~Game() {
	delete this->A;
	delete this->B;
}
bool Game::initGame(int argc, char* argv[], CommonPlayer* playerA, CommonPlayer* playerB) {
	bool result = true;
	std::string path = ".";
	DIR * dir;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-quiet") == 0) {
			this->displayGame = false;
		}
		else if (strcmp(argv[i-1],"-delay") == 0) {
			this->delay = atoi(argv[i]);
		}
		else if (i==1){
			path = argv[i];
		}
	}
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << (path == "." ? "Working Directory" : path) << std::endl;
		result = false;
	}
	closedir(dir);
	if (result) {
		result = setupGame(path);
	}
	this->A = playerA;
	this->B = playerB;
	return result;
}

bool Game::setupGame(const std::string& path) {
	bool result;
	//this->A = new SmartPlayer();
	//this->B = new SmartPlayer();
	result = this->gameBoard.initBoard(path, this->A, this->B, 10, 10, this->displayGame);
		if (result) {
			this->turn = 0;
			this->A->setBoard(0, const_cast<const char**>(this->gameBoard.getPlayerABoard()), 10, 10);
			this->B->setBoard(1, const_cast<const char**>(this->gameBoard.getPlayerBBoard()), 10, 10);
			result = (result & this->A->init(path));
			result = (result & this->B->init(path));
		}
	return result;
}

bool Game::playGame() {
	Sleep(this->delay);
	while (this->turn >= 0) {
		std::pair<int, int> nextMove;
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
		}if (nextMove.first == -1 || nextMove.second == -1) {
			if (!(this->setNextTurn(AttackResult::Miss, false))) {
				return false;
			}
		}
		/**/
		if (turn == 0) {
		std::cout << "player A is about to attack at: " << nextMove.first << " , " << nextMove.second << std::endl;
		}if (turn == 1) {
			std::cout << "player B is about to attack at: " << nextMove.first << " , " << nextMove.second << std::endl;
		}
		bool selfHit = false;
		res = this->gameBoard.play_attack(nextMove, this->turn, &selfHit);
		std::cout << "attack result is: ";
		if (res == AttackResult::Hit) {
			std::cout << "hit" << std::endl;
		}else if (res == AttackResult::Miss) {
			std::cout << "miss" << std::endl;
		}else if (res == AttackResult::Sink) {
			std::cout << "sink" << std::endl;
		}

		this->A->notifyOnAttackResult(turn, nextMove.first, nextMove.second, res);
		this->B->notifyOnAttackResult(turn, nextMove.first, nextMove.second, res);
		if (this->displayGame && nextMove.first != -1 && nextMove.second != -1) {
			this->gameBoard.displayAttack(res, nextMove.first, nextMove.second, this->delay);
		}
		if (!(this->setNextTurn(res, selfHit))) {
			return false;
		}
	}

	if (!this->endGame()) {
		return false;
	}

	return true;
}


bool Game::setNextTurn(AttackResult res, bool selfHit) {
	//check for victory
	if (this->A->hasNoMoreBoats()) {
		//player A is out of boats - player B wins
		this->winner = 'B';
		this->B->addWin();
		this->turn = -1;
		return true;
	}
	else if (this->B->hasNoMoreBoats()) {
		//player B is out of boats - player A wins
		this->winner = 'A';
		this->A->addWin();
		this->turn = -1;
		return true;
	}

	//check if one or both playes have finished attacking
	if (this->A->hasFinishedAttacking()) {
		if (this->B->hasFinishedAttacking()) {
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
	else if (this->B->hasFinishedAttacking()) {
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
	GameBoard::setTextColor(15);
	//system("cls");
	switch (this->turn) {
		case -1:
			std::cout << "Player " << this->winner << " won" << std::endl;
		case -2:
			std::cout << "Points:" << std::endl;
			std::cout << "Player A: " << this->A->getGameScore() << std::endl;
			std::cout << "Player B: " << this->B->getGameScore() << std::endl;
			return true;
		default:
			std::cout << "Error! reached 'endGame' function with invalid 'turn'" << std::endl;
			return false;
	}
}