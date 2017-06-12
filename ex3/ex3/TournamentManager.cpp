#include "TournamentManager.h"
#include "SingleGame.h"

#include <map>
#include <memory>
#include <thread>
#include <algorithm>
#include <ctime>
#include <iomanip>

bool TournamentManager::initTournament(std::string path) {
	DIR * dir;
	bool result = true;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << (path == "." ? "Working Directory" : path) << std::endl;
		closedir(dir);
		return false;
	}
	closedir(dir);

	setUpLogger(path);
	result = setUpBoards(path);
	result = result && setUpPlayers(path);
	std::cout << "Number of legal players: " << this->players.size() << std::endl;
	std::cout << "Number of legal boards: " << this->gameBoards.size() << std::endl;

	if (result) {
		createGameCombinations();
		logTournamentStatistics();
		size_t numOfRounds = (this->players.size() - 1) * 2 * this->gameBoards.size();
		this->playedRounds.resize(numOfRounds, 0);
	}
	return result;
}

void TournamentManager::setUpLogger(const std::string& path) {
	std::string loggerFile;
	if (path == ".") { //no dir path is given
		loggerFile = "game.log";
	}
	else if (path.back() == '/') { //dir path includes '/'
		loggerFile = path + "game.log";
	}
	else {
		loggerFile = path + "/" + "game.log";
	}
	this->logger.InitLog(loggerFile);
	this->logger.logMessage("Started running a game tournament!");
}

bool TournamentManager::setUpBoards(const std::string & path) {
	std::string errorPath = path == "." ? "Working Directory" : path;

	this->boardFileLister = FilesListerWithSuffix(path);
	if (this->boardFileLister.getFilesList().empty()) {
		std::cout << "Missing board file (*.sboard) looking in path: " << errorPath << std::endl;
		return false;
	}
	for (size_t i = 0; i < this->boardFileLister.getFilesList().size(); i++) {
		std::shared_ptr<Board> nextBoard = std::make_shared<Board>();
		if (nextBoard->loadBoard(this->boardFileLister.getFilesList().at(i), &this->logger)) {
			this->gameBoards.push_back(nextBoard);
		}
	}

	if (this->gameBoards.empty()) {
		return false;
	}

	return true;
}

bool TournamentManager::setUpPlayers(const std::string & path) {
	HANDLE dir;
	WIN32_FIND_DATAA fileData; //data struct for file
	GetAlgorithmFuncType getAlgorithmFunc;

	int i = 0;
	// iterate over *.dll files in path
	std::string s = "\\*.dll"; // only .dll endings
	dir = FindFirstFileA((path + s).c_str(), &fileData); // Notice: Unicode compatible version of FindFirstFile
	if (dir != INVALID_HANDLE_VALUE) { //check if the dir opened successfully	
									   // test each file suffix and set variables as needed
		do {
			std::string fileName = fileData.cFileName;
			std::string fullFileName = path + "\\" + fileName;
			std::string algoName = fileName.substr(0, fileName.find("."));

			// Load dynamic library
			HINSTANCE hDll = LoadLibraryA(fullFileName.c_str()); // Notice: Unicode compatible version of LoadLibrary
			if (!hDll) {
				this->logger.logMessage("Cannot load dll: " + fullFileName);
			}

			// Get function pointer
			getAlgorithmFunc = (GetAlgorithmFuncType)GetProcAddress(hDll, "GetAlgorithm");
			if (!getAlgorithmFunc) {
				this->logger.logMessage("Cannot load dll: " + fullFileName);
			}
			else {
				std::shared_ptr<PlayerData> player = std::make_shared<PlayerData>(i++, make_tuple(algoName, hDll, getAlgorithmFunc));
				this->players.push_back(player);
				if (algoName.length() > this->nameBuffer) {
					this->nameBuffer = algoName.length(); //used later to print organized results
				}
			}
		} while (FindNextFileA(dir, &fileData)); // Notice: Unicode compatible version of FindNextFile
	}
	if (this->players.size() < 2) {
		std::string err_msg = "Missing an algorithm (dll) file looking in path: ";
		err_msg += (path == "." ? "Working Directory" : path);
		std::cout << err_msg << std::endl;
		this->logger.logMessage(err_msg);
		return false;
	}
	this->nameBuffer += 5;
	return true;
}

void TournamentManager::createGameCombinations() {
	for (size_t k = 0; k < this->gameBoards.size(); k++) {
		for (size_t i = 0; i < this->players.size(); i++) {
			for (size_t j = 0; j < this->players.size(); j++) {
				if (i != j) {
					std::shared_ptr<PlayerData> A = this->players.at(i);
					std::shared_ptr<PlayerData> B = this->players.at(j);
					std::shared_ptr<Board> board = this->gameBoards.at(k);
					this->games.push_back(std::make_tuple(A, B, board));
				}
			}
		}
	}
	srand(unsigned(time(NULL)));
	std::random_shuffle(this->games.begin(), this->games.end());
}

void TournamentManager::logTournamentStatistics() {
	const std::string base = "The tournament contains ";

	this->logger.logMessage(base + std::to_string(this->players.size()) + " players");
	this->logger.logMessage(base + std::to_string(this->gameBoards.size()) + " boards");
	this->logger.logMessage(base + std::to_string(this->games.size()) + " games");
}

bool TournamentManager::playTournament() {

	for (auto & t : this->threads_vec) {
		t = std::thread(&TournamentManager::threadRunner, this);
	}
	
	while (runningThreads > 0) {
		std::unique_lock<std::mutex> lk(this->resultsMutex);
		this->cv.wait(lk, [this] {
			return this->playedRounds[this->roundCounter] == this->players.size(); });
		intermediateResults(this->roundCounter++);
		lk.unlock();
	}

	for (auto & t : this->threads_vec) {
		t.join();
	}
	this->logger.logMessage("printing residual rounds' results");
	while(this->roundCounter < this->playedRounds.size()) {
		intermediateResults(this->roundCounter++);
	}
	this->logger.logMessage("The tournament has ended");
	return true;
}

void TournamentManager::threadRunner() {
	this->runningThreads++;
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> gameStats;
	while ((gameStats = getNextGame()) != std::make_tuple(nullptr, nullptr, nullptr)) {
		std::unique_ptr<SingleGame> game = std::make_unique<SingleGame>(gameStats);
		std::pair<int, int> playedRounds;// = play game 
		increaseRoundCount(playedRounds.first, playedRounds.second);

	}
	this->runningThreads--;
}

void TournamentManager::increaseRoundCount(int roundA, int roundB) {
	static std::mutex roundMutex;
	std::lock_guard<std::mutex> l(roundMutex);
	this->playedRounds[roundA] += 1;
	this->playedRounds[roundB] += 1;
	if (this->playedRounds[roundA] == this->players.size() || this->playedRounds[roundB] == this->players.size()) {
		this->cv.notify_one();
	}
}

void TournamentManager::intermediateResults(int round) {
	system("cls");
	std::vector<std::tuple<int, int, int, int, std::string>> playersResults;
	for (std::shared_ptr<PlayerData> player : this->players) {
		playersResults.push_back(player->gotRoundData(round));
	}
	std::sort(playersResults.begin(), playersResults.end());
	std::cout << std::left << std::setw(8) << "#" << std::setw(this->nameBuffer) << "Team Name";
	std::cout << std::setw(8) << "Wins" << std::setw(8) << "Losses" << std::setw(8) << "%";
	std::cout << std::setw(8) << "Pts For" << std::setw(8) << "Pts Against" << std::endl;

	for (int i = 0; i < playersResults.size(); i++) {
		std::cout << std::setw(8) << std::to_string(i + 1) + '.';
		std::cout << std::setw(this->nameBuffer) << std::get<4>(playersResults.at(i));
		std::cout << std::setw(8) << std::get<0>(playersResults.at(i));
		std::cout << std::setw(8) << std::get<2>(playersResults.at(i));
		std::cout << std::setw(8) << std::setprecision(2) << (double)std::get<0>(playersResults.at(i)) / round;
		std::cout << std::setw(8) << std::get<1>(playersResults.at(i));
		std::cout << std::setw(8) << std::get<3>(playersResults.at(i)) << std::endl;
		}
	this->logger.logResults(playersResults, this->nameBuffer, round);
}

std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>,
	std::shared_ptr<Board>> TournamentManager::getNextGame() {
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<Board>> nextGame;
	static std::mutex gameMutex;
	std::lock_guard<std::mutex> l(gameMutex);
	if (this->games.empty()) {
		nextGame = std::make_tuple(nullptr, nullptr, nullptr);
	}
	else {
		nextGame = this->games.front();
		this->games.pop_front();
	}

	return nextGame;
}
