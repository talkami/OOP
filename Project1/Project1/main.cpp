#include "Game.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	std::string path;
	DIR * dir;
	bool initializedSuccessfully, successfulPlay;
	
	if (argc > 1) {
		path = argv[1];
	}
	else {
		path = "";
	}
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << path << std::endl;
		return -1;
	}
	closedir(dir);
	Game* newGame = new Game();
	initializedSuccessfully = newGame->initGame(path);
	if (!initializedSuccessfully) {
		return -1;
	}
	successfulPlay = newGame->playGame();
	if (!successfulPlay) {
		return -1;
	}

	Sleep(20000);
	
	return 0;
}