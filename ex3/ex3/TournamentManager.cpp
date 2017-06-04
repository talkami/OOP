#include "TournamentManager.h"
#include <algorithm>
#include <ctime>

bool TournamentManager::initGame(std::string path, int threads) {
	DIR * dir;
	bool result = true;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << (path == "." ? "Working Directory" : path) << std::endl;
		closedir(dir);
		return false;
	}
	closedir(dir);
	
	setUpLogger(path);
	this->logger.logMessage("test message1");
	Sleep(1000);
	this->logger.logMessage("test message2");
	/*result = getBoards(path) && getDLLs(path);
	std::cout << "Number of legal players: " << this->players_vec.size() << std::endl;
	std::cout << "Number of legal boards: " << this->gameBoards.size() << std::endl;

	createPlayerData();
	createGameCombinations();*/
	return result;
}

void TournamentManager::setUpLogger(std::string& path) {
	std::string loggerFile;
	if (path == ".") { //no dir path is given
		loggerFile = "game.log";
	}
	if (path.back() == '/') { //dir path includes '/'
		loggerFile = path + "game.log";
	}
	loggerFile = path + "/" + "game.log";
	this->logger.InitLog(loggerFile);
	this->logger.logMessage("Started running a game tournament");
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
				std::cout << "Cannot load dll: " << fullFileName << std::endl;
				return false;
			}

			// Get function pointer
			getAlgorithmFunc = (GetAlgorithmFuncType)GetProcAddress(hDll, "GetAlgorithm");
			if (getAlgorithmFunc) {
				this->players_vec.push_back(make_tuple(algoName, hDll, getAlgorithmFunc));
			}

		} while (FindNextFileA(dir, &fileData)); // Notice: Unicode compatible version of FindNextFile
	}
	if (this->players_vec.size() < 2) {
		std::cout << "Missing an algorithm (dll) file looking in path: ";
		std::cout << (path == "." ? "Working Directory" : path) << std::endl;
		return false;
	}
	return true;
}
void TournamentManager::createPlayerData() {

}

void TournamentManager::createGameCombinations() {
	for (size_t i = 0; i < this->players.size(); i++) {
		for (size_t j = 0; j < this->players.size(); j++) {
			if (i != j){
				for (size_t k = 0; k < this->gameBoards.size(); k++) {
					PlayerData* A = &this->players.at(i);
					PlayerData* B = &this->players.at(j);
					GameBoard* board = this->gameBoards.at(k);
					this->games.push_back(std::make_tuple(A, B, board));
				}
			}
		}
	}
	srand(unsigned(time(NULL)));
	std::random_shuffle(this->games.begin(), this->games.end());
}

bool TournamentManager::playGame() {
	// TODO: Complete function!
	return true;
}
