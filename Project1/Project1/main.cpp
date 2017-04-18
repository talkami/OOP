#include "Game.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
	char x;
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
		std::cin >> x;
		return -1;
	}
	closedir(dir);
	Game* newGame = new Game();
	initializedSuccessfully = newGame->initGame(path);
	if (!initializedSuccessfully) {
		std::cin >> x;
		return -1;
	}
	successfulPlay = newGame->playGame();
	if (!successfulPlay) {
		std::cin >> x;
		return -1;
	}

	std::cin >> x;

	return 0;
}