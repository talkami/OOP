#include "Game.h"

int main(int argc, char* argv[]) {
	bool initializedSuccessfully, successfulPlay;
	Game* newGame;

	newGame = new Game();
	initializedSuccessfully = newGame->initGame(argc, argv);
	if (!initializedSuccessfully) {
		return -1;
	}
	successfulPlay = newGame->playGame();
	if (!successfulPlay) {
		return -1;
	}
	
	return 0;
}
