#include "Player.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

void Player::setBoard(const char** board, int numRows, int numCols) {
	memcpy(this->player_board, board, sizeof(char) * numRows * numCols);

}

std::pair<int, int> Player::attack() {
	if (this->attackNumber >= this->maxMoves) {
		return NULL;
	}
	return this->attackMoves[this->attackNumber++];
}

void Player::getMoves(const string& attackFile) {
	this->attackMoves.clear();
	ifstream fin(attackFile);
	string line;
	while (getline(fin, line)){ 
		this->processLine(line);
	}
	this->attackNumber = 0;
	this->maxMoves = this->attackMoves.size();
}

void Player::processLine(const string& line) {
	vector<string> tokens = split(line, ',');
	int num1;
	int num2;
	if (tokens.size() < 2) {
		return;
	}
	try {
		num1 = stoi(tokens[0]);
		num2 = stoi(tokens[1]);
	}
	catch (std::invalid_argument& e) {
		return;
	}
	if ((num1 <1) || (num1 > 10) || (num2 < 1) || (num2 > 10)) {
		return;
	}

	pair<int, int> aPair(num1, num2);	
	this->attackMoves.push_back(aPair);
	
}

std::vector<std::string> Player::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream strSt(s);
	std::string item;

	while (std::getline(strSt, item, delim)){ 
		elems.push_back(item); 
	}

	return elems;
}

bool Player::hasFinishedAttacking() {
	if (this->attackNumber >= this->maxMoves) {
		return true;
	}
	else {
		return false;
	}
}
void notifyOnAttackResult(int player, int row, int col, AttackResult result) {};

bool Player::hasNoMoreBoats(){
	
}
