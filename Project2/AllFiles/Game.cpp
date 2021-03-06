#include "Game.h"

Game::~Game() {
	// close all the dynamic libs we opened
	for (vitr = this->dll_vec.begin(); vitr != dll_vec.end(); ++vitr){
		FreeLibrary(std::get<1>(*vitr));
	}
	delete this->A;
	delete this->B;
}

bool Game::initGame(int argc, char* argv[]) {
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

bool Game::setupPlayers(const std::string& path) {
	HANDLE dir;
	WIN32_FIND_DATAA fileData; //data struct for file
	std::string s = "\\*.dll"; // only .dll endings
	dir = FindFirstFileA((path + s).c_str(), &fileData); // Notice: Unicode compatible version of FindFirstFile
	if (dir != INVALID_HANDLE_VALUE) {//check if the dir opened successfully
		for (int i = 0; i < 2; i++) {
			std::string fileName = fileData.cFileName;
			std::string fullFileName = path + "\\" + fileName;
			std::string algoName = fileName.substr(0, fileName.find("."));
			// Load dynamic library
			HINSTANCE hDll = LoadLibraryA(fullFileName.c_str()); // Notice: Unicode compatible version of LoadLibrary
			if (!hDll){
				std::cout << "Cannot load dll: " << fullFileName << std::endl;
				return false;
			}

			// Get function pointer
			getAlgorithmFunc = (GetAlgorithmFuncType)GetProcAddress(hDll, "GetAlgorithm");
			if (!getAlgorithmFunc){
				std::cout << "Cannot load dll: " << fullFileName << std::endl;
				return false;
			}
			this->dll_vec.push_back(make_tuple(algoName, hDll, getAlgorithmFunc));
			if (!FindNextFileA(dir, &fileData) && i==0) {
				std::cout << "Missing an algorithm (dll) file looking in path: ";
				std::cout << (path == "." ? "Working Directory" : path) << std::endl;
				return false;
			}
		}
	}
	else {
		std::cout << "Missing an algorithm (dll) file looking in path: ";
		std::cout << (path == "." ? "Working Directory" : path) << std::endl;
		return false;
	}
	this->A = (*std::get<2>(this->dll_vec[0]))();
	this->B = (*std::get<2>(this->dll_vec[1]))();

	return true;
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
			if (turn == 0) {
				this->AFinishedAttacking = true;
			}
			else if (turn == 1){
				this->BFinishedAttacking;
			}
			if (!(this->setNextTurn(AttackResult::Miss, false))) {
				return false;
			}
		}
		bool selfHit = false;
		res = this->gameBoard.play_attack(nextMove, this->turn, &selfHit);

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
	if (this->gameBoard.hasNoMoreBoats(0)) {
		//player A is out of boats - player B wins
		this->winner = 'B';
		this->turn = -1;
		return true;
	}
	else if (this->gameBoard.hasNoMoreBoats(1)) {
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

bool Game::endGame() {
	GameBoard::setTextColor(15);
	//system("cls");
	switch (this->turn) {
	case -1:
		std::cout << "Player " << this->winner << " won" << std::endl;
	case -2:
		std::cout << "Points:" << std::endl;
		std::cout << "Player A: " << this->gameBoard.getGameScore(0) << std::endl;
		std::cout << "Player B: " << this->gameBoard.getGameScore(1) << std::endl;
		return true;
	default:
		std::cout << "Error! reached 'endGame' function with invalid 'turn'" << std::endl;
		return false;
	}
}