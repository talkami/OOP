#include "TournamentManager.h"
#include <algorithm>
#include <ctime>

bool TournamentManager::initTournament(std::string path, int threads) {
	DIR * dir;
	bool result = true;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << (path == "." ? "Working Directory" : path) << std::endl;
		closedir(dir);
		return false;
	}
	closedir(dir);
	
	setUpLogger(path);
	result = getBoards(path) && getDLLs(path);
	std::cout << "Number of legal players: " << this->players_dll.size() << std::endl;
	std::cout << "Number of legal boards: " << this->gameBoards.size() << std::endl;

	createPlayerData();
	createGameCombinations();
	logTournamentStatistics();
	return result;
}

void TournamentManager::setUpLogger(const std::string& path) {
	std::string loggerFile;
	if (path == ".") { //no dir path is given
		loggerFile = "game.log";
	}
	if (path.back() == '/') { //dir path includes '/'
		loggerFile = path + "game.log";
	}
	loggerFile = path + "/" + "game.log";
	this->logger.InitLog(loggerFile);
	this->logger.logMessage("Started running a game tournament!");
}

bool TournamentManager::getBoards(const std::string & path){
	std::string errorPath = path == "." ? "Working Directory" : path;

	this->boardFileLister = FilesListerWithSuffix(path);
	if (this->boardFileLister.getFilesList().size() == 0) {
		std::cout << "Missing board file (*.sboard) looking in path: " << errorPath << std::endl;
		return false;
	}

	
	return true;
}

bool TournamentManager::getDLLs(const std::string & path){
	HANDLE dir;
	WIN32_FIND_DATAA fileData; //data struct for file

	// iterate over *.dll files in path
	std::string s = "\\*.dll"; // only .dll endings
	dir = FindFirstFileA((path + s).c_str(), &fileData); // Notice: Unicode compatible version of FindFirstFile
	if (dir != INVALID_HANDLE_VALUE) //check if the dir opened successfully
	{
		// test each file suffix and set variables as needed
		do
		{
			std::string fileName = fileData.cFileName;
			std::string fullFileName = path + "\\" + fileName;
			std::string algoName = fileName.substr(0, fileName.find("."));

			// Load dynamic library
			HINSTANCE hDll = LoadLibraryA(fullFileName.c_str()); // Notice: Unicode compatible version of LoadLibrary
			if (!hDll){
				this->logger.logMessage("Cannot load dll: " + fullFileName);
			}

			// Get function pointer
			getAlgorithmFunc = (GetAlgorithmFuncType)GetProcAddress(hDll, "GetAlgorithm");
			if (getAlgorithmFunc) {
				this->players_dll.push_back(make_tuple(algoName, hDll, getAlgorithmFunc));
			}

		} while (FindNextFileA(dir, &fileData)); // Notice: Unicode compatible version of FindNextFile
	}
	if (this->players_dll.size() < 2) {
		std::string err_msg = "Missing an algorithm (dll) file looking in path: ";
		err_msg += path == "." ? "Working Directory" : path;
		std::cout << err_msg << std::endl;
		this->logger.logMessage(err_msg);
		return false;
	}
	return true;
}

void TournamentManager::createPlayerData() {
	for (int i = 0; i < this->players_dll.size(); i++) {
		std::shared_ptr<PlayerData> player = std::make_shared<PlayerData>(i);
		this->players.push_back(player);
	}
}


void TournamentManager::createGameCombinations() {
	for (size_t k = 0; k < this->gameBoards.size(); k++) {
		for (size_t i = 0; i < this->players.size(); i++) {
			for (size_t j = 0; j < this->players.size(); j++) {
				if (i != j){
					std::shared_ptr<PlayerData> A = this->players.at(i);
					std::shared_ptr<PlayerData> B = this->players.at(j);
					std::shared_ptr<GameBoard> board = this->gameBoards.at(k);
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
	const std::string playerString = base + std::to_string(this->players.size()) + " players";
	const std::string boardString = base + std::to_string(this->gameBoards.size()) + " boards";
	const std::string gameString = base + std::to_string(this->games.size()) + " games";
	this->logger.logMessage(playerString);
	this->logger.logMessage(boardString);
	this->logger.logMessage(gameString);
}


bool TournamentManager::playTournament() {

	// TODO: Complete function!
	return true;
}

void TournamentManager::startSingleGame() {

}

std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<GameBoard>> TournamentManager::getNextGame() {
	std::tuple<std::shared_ptr<PlayerData>, std::shared_ptr<PlayerData>, std::shared_ptr<GameBoard>> nextGame;
	static std::mutex m;
	std::lock_guard<std::mutex> l(m);
	if (this->games.empty()) {
		nextGame = std::make_tuple(nullptr, nullptr, nullptr);
	}
	else {
		nextGame = this->games.front();
		this->games.pop_front();
	}

	return nextGame;
}