#include "Game.h"

int main(int argc, char* argv[]){
	char x;
	bool initializedSuccessfully, successfulPlay;
	Game* newGame;

	newGame = new Game();
	initializedSuccessfully = newGame->initGame(argc, argv);
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