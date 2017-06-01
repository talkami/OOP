#include "TournamentManager.h"

int main(int argc, char* argv[]) {
	bool initializedSuccessfully, successfulPlay;
	TournamentManager* game;
	std::string path = ".";
	int threads = 4;
	DIR * dir;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i - 1], "-threads") == 0) {
			this->numOfThreads = atoi(argv[i]) > 0 ? atoi(argv[i]) : 0;
		}
		else if (i == 1) {
			path = argv[i];
		}
	}

	game = new TournamentManager();

	initializedSuccessfully = game->initGame(path, threads);
	if (!initializedSuccessfully) {
		return -1;
	}
	successfulPlay = game->playGame();
	if (!successfulPlay) {
		return -1;
	}

	return 0;
}