#include "TournamentManager.h"

#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
	bool initializedSuccessfully, successfulPlay;
	std::string path = ".";
	int threads = 4;
	if (argc > 1) {
		if (strcmp(argv[1], "-threads") == 0 && argc > 2) {
			threads = atoi(argv[2]) > 0 ? atoi(argv[2]) : threads;
		}
		else {
			path = argv[1];
			if (strcmp(argv[2], "-threads") == 0 && argc > 3) {
				threads = atoi(argv[3]) > 0 ? atoi(argv[3]) : threads;
			}
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
