#include "TournamentManager.h"

int main(int argc, char* argv[]) {
	bool initializedSuccessfully, successfulPlay;
	TournamentManager* game = new TournamentManager();

	initializedSuccessfully = game->initGame(argc, argv);
	if (!initializedSuccessfully) {
		return -1;
	}
	successfulPlay = game->playGame();
	if (!successfulPlay) {
		return -1;
	}

	return 0;
}