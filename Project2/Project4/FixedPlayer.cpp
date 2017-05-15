
#include "FixedPlayer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>


void FixedPlayer::setBoard(int player, const char** board, int numRows, int numCols) {
	setProperties(player, numRows, numCols);
}

bool FixedPlayer::init(const std::string & path){

	bool result = true;
	std::string errorPath;
	if (path == ".") {
		errorPath = "Working Directory";
	}
	else {
		errorPath = path;
	}
	if (this->playerNum == 0) {
		AttackAFileLister playerAFileLister = AttackAFileLister(path);
		if (playerAFileLister.getFilesList().size() == 0) {
			std::cout << "Missing attack file for player A (*.attack-a) looking in path: " << errorPath << std::endl;
			result = false;
		}
		if (result) {
			getMoves(playerAFileLister.getFilesList()[0]);
		}

	}
	else {
		AttackBFileLister playerBFileLister = AttackBFileLister(path);
		if (playerBFileLister.getFilesList().size() == 0) {
			std::cout << "Missing attack file for player B (*.attack-b) looking in path: " << errorPath << std::endl;
			result = false;
		}if (result) {
			getMoves(playerBFileLister.getFilesList()[0]);
		}
	}
	return result;
}

std::pair<int, int> FixedPlayer::attack() {
	if (this->attackNumber >= this->maxMoves) {
		std::pair<int, int> res(-1, -1);
		return res;
	}
	return this->attackMoves[this->attackNumber++];
}

void FixedPlayer::getMoves(const std::string& attackFile) {
	this->attackMoves.clear();
	std::ifstream fin(attackFile);
	std::string line;
	while (getline(fin, line)){ 
		this->processLine(line);
	}
	this->attackNumber = 0;
	this->maxMoves = this->attackMoves.size();
}

void FixedPlayer::processLine(const std::string& line) {
	std::vector<std::string> tokens = split(line, ',');
	int num1;
	int num2;
	if (tokens.size() < 2) {
		return;
	}
	try {
		num1 = stoi(tokens[0]);
		num2 = stoi(tokens[1]);
	}
	catch (std::invalid_argument& ) {
		return;
	}
	if ((num1 < 1) || (num1 > 10) || (num2 < 1) || (num2 > 10)) {
		return;
	}

	std::pair<int, int> aPair(num1, num2);	
	this->attackMoves.push_back(aPair);
	return;	
}

std::vector<std::string> FixedPlayer::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream strSt(s);
	std::string item;

	while (std::getline(strSt, item, delim)){ 
		elems.push_back(item); 
	}

	return elems;
}

bool FixedPlayer::hasFinishedAttacking() {
	if (this->attackNumber >= this->maxMoves) {
		return true;
	}
	else {
		return false;
	}
}
void FixedPlayer::notifyOnAttackResult(int player, int row, int col, AttackResult result) {}


IBattleshipGameAlgo* GetAlgorithm(){
	_instancesVec.push_back(new FixedPlayer());					// Create new instance and keep it in vector
	return _instancesVec[_instancesVec.size() - 1];			// Return last instance
}