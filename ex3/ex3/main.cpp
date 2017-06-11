#include "TournamentManager.h"

int main(int argc, char* argv[]) {
	bool initializedSuccessfully, successfulPlay;
	std::string path = ".";
	int threads = 4;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i - 1], "-threads") == 0) {
			threads = atoi(argv[i]) > 0 ? atoi(argv[i]) : 0;
		}
		else if (i == 1) {
			path = argv[i];
		}
	}

	TournamentManager* game = new TournamentManager(threads);

	initializedSuccessfully = game->initTournament(path);
	if (!initializedSuccessfully) {
		return -1;
	}
	successfulPlay = game->playTournament();
	if (!successfulPlay) {
	return -1;
	}

	return 0;
}
