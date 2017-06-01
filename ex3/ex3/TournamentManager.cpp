#include "TournamentManager.h"


bool TournamentManager::initGame(std::string path, int threads) {
	bool result = true;
	if ((dir = opendir(path.c_str())) == NULL) {
		std::cout << "Wrong path: " << (path == "." ? "Working Directory" : path) << std::endl;
		closedir(dir);
		return false;
	}
	closedir(dir);

	result = getBoards(path) && getDLLs(path);
	std::cout << "Number of legal players: " << this->players_vec.size() << std::endl;
	std::cout << "Number of legal boards: " << this->gameBoards.size() << std::endl;

	return result;
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
	else {
		std::cout << "Missing an algorithm (dll) file looking in path: ";
		std::cout << (path == "." ? "Working Directory" : path) << std::endl;
		return false;
	}
	if (this->players_vec.size() < 2) {
		std::cout << "Missing an algorithm (dll) file looking in path: ";
		std::cout << (path == "." ? "Working Directory" : path) << std::endl;
		return false;
	}
	return true;
}

bool TournamentManager::playGame() {
	// TODO: Complete function!
	return true;
}
