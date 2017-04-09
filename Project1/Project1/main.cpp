#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "Boat.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	std::string path = "";
	if (argc > 1) {
		path = argv[1];
	}
	DIR * dir;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: <" << this->m_basePath << ">" << std::endl;
		return -1;
	}
	closedir(dir);

	bool ErrorOccured = false;
	SeaBattleBoardLister seaBattleBoardLister = SeaBattleBoardLister(path);
	if (seaBattleBoardLister.getFilesList().size() == 0) {
		std::cout << "Missing board file (*.sboard) looking in path: <" + path + ">" << std::endl;
		ErrorOccured = true;
	}else{
		std::string boardFile = seaBattleBoardLister.getFilesList()[0];
	}
	AttackAFileLister algoAattackFileLister = AttackAFileLister(path);
	if (algoAattackFileLister.getFilesList().size() == 0) {
		std::cout << "Missing attack file for player A (*.attack-a) looking in path: <" + path + ">" << std::endl;
		ErrorOccured = true;
	}else{
		std::string boardFile = algoAattackFileLister.getFilesList()[0];
	}
	AttackBFileLister algoBattackFileLister = AttackBFileLister(path);
	if (algoBattackFileLister.getFilesList().size() == 0) {
		std::cout << "Missing attack file for player B (*.attack-b) looking in path: <" + path + ">" << std::endl;
		ErrorOccured = true;
	}else{
		std::string boardFile = algoBattackFileLister.getFilesList()[0];
	}
	if (ErrorOccured) {
		return -1;
	}



}