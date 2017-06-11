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

	this->board = board;
	return true;
}



bool SingleGame::playSingleGame() {
	//Sleep(this->delay);
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
		}if (nextMove->getRow == -1 || nextMove->getCol == -1 ||nextMove->getDepth == -1) {
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

	if (!this->endGame()) {
		return false;
	}

	return true;
}

bool SingleGame::setNextTurn(AttackResult res, bool selfHit) {
	//check for victory
	if (this->board->hasNoMoreBoats(0)) {
		//player A is out of boats - player B wins
		this->winner = 'B';
		this->turn = -1;
		return true;
	}
	else if (this->board->hasNoMoreBoats(1)) {
		//player B is out of boats - player A wins
		this->winner = 'A';
		this->turn = -1;
		return true;
	}

	//check if one or both playes have finished attacking
	if (this->AFinishedAttacking) {
		if (this->BFinishedAttacking) {
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

bool SingleGame::endGame() {
	GameBoard::setTextColor(15);
	//system("cls");

	//what to do when single game is over?
	switch (this->turn) {
	case -1:
		std::cout << "Player " << this->winner << " won" << std::endl;
	case -2:
		std::cout << "Points:" << std::endl;
		std::cout << "Player A: " << this->board.getGameScore(0) << std::endl;
		std::cout << "Player B: " << this->board.getGameScore(1) << std::endl;
		return true;
	default:
		std::cout << "Error! reached 'endGame' function with invalid 'turn'" << std::endl;
		return false;
	}
}






//delete? ask tal!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool SingleGame::initGame(int argc, char* argv[]) {
	bool result = true;
	std::string path = ".";
	DIR * dir;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-quiet") == 0) {
			this->displayGame = false;
		}
		else if (strcmp(argv[i - 1], "-delay") == 0) {
			this->delay = atoi(argv[i]);
		}
		else if (i == 1) {
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
	return result;
}

//delete? ask tal!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool Game::setupGame(const std::string& path) {
	bool result;
	result = this->gameBoard.initBoard(path, this->A, this->B, 10, 10, this->displayGame);
	result = (result & setupPlayers(path));
	if (result) {
		this->A->setBoard(0, const_cast<const char**>(this->gameBoard.getPlayerABoard()), 10, 10);
		this->B->setBoard(1, const_cast<const char**>(this->gameBoard.getPlayerBBoard()), 10, 10);
		result = (result & this->A->init(path));
		result = (result & this->B->init(path));
	}
	if (result && this->displayGame) {
		this->gameBoard.displayBoard();
	}

	return result;
}