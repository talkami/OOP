#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>

void Board::getBoard(const string& boardFile) {
	ifstream fin(boardFile);
	for (int i = 0; i < 10; i++) {
		std::getline(fin, board[i]);
	}
}
