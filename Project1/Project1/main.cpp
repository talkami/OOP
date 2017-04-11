#include "Game.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	std::string path;
	DIR * dir;
	Game newGame;
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

	newGame = Game();
	initializedSuccessfully = newGame.initGame(path);
	if (!initializedSuccessfully) {
		return -1;
	}
	successfulPlay = newGame.playGame();
	if (!successfulPlay) {
		return -1;
	}


	return 0;
}