#include "Game.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	std::cout << "Started main" << std::endl;
	std::string path;
	DIR * dir;
	bool initializedSuccessfully, successfulPlay;
	
	if (argc > 1) {
		path = argv[1];
	}
	else {
		path = "";
	}
	std::cout << "got path: " << path << ". Checking path" << std::endl;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << path << std::endl;
		return -1;
	}
	closedir(dir);
	std::cout << "path check completed creating game." << std::endl;
	Game newGame = Game();
	std::cout << "game created. Initializing game" << std::endl;
	initializedSuccessfully = newGame.initGame(path);
	if (!initializedSuccessfully) {
		return -1;
	}
	std::cout << "game initialized sucessfully. Playing game." << std::endl;
	successfulPlay = newGame.playGame();
	if (!successfulPlay) {
		return -1;
	}
	
	return 0;
}