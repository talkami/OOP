#include "Game.h"
#include <iostream> 
#include <map> 
#include <vector>
#include <string> 
#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	char x;
	bool initializedSuccessfully, successfulPlay;
	Game* newGame;

	//dll file handler

	HANDLE dir;
	
	WIN32_FIND_DATAA fileData; //data struct for file
	std::vector<HINSTANCE>::iterator itr;

	// vector of shape objects we create
	std::vector<IBattleshipGameAlgo *> battleship_vec;  
	std::vector<IBattleshipGameAlgo *>::iterator sitr;
	
	// define function of the type we expect
	typedef IBattleshipGameAlgo *(*GetAlgorithmFuncType)(); 
	GetAlgorithmFuncType getAlgorithmFunc;

	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>> dll_vec; // vector of <Shape Name, dll handle, GetShape function ptr>
	std::vector<std::tuple<std::string, HINSTANCE, GetAlgorithmFuncType>>::iterator vitr;

   // iterate over *.dll files in path
   if (argc <2){
		std::string path("");
   }
   else {
	char * pathVar = argv[1];
	std::string path(pathVar); //Here you should take actual folder
   }
   
	std::string s = "\\*.dll"; // only .dll endings
	dir = FindFirstFileA((path + s).c_str(), &fileData); // Notice: Unicode compatible version of FindFirstFile
	if(dir != INVALID_HANDLE_VALUE) //check if the dir opened successfully
	{
		for (int i = 0; i<2 ;i++)
		{
			if (!FindNextFileA(dir, &fileData)){
				std::cout << "less then 2 dll files" << std::endl;
				return EXIT_FAILURE;
			}
			std::string fileName = fileData.cFileName;
			std::string fullFileName = path + "\\" + fileName;
			std::string algoName = fileName.substr(0, fileName.find("."));
			
			// Load dynamic library
			HINSTANCE hDll = LoadLibraryA(fullFileName.c_str()); // Notice: Unicode compatible version of LoadLibrary
			if(!hDll)
			{
				std::cout << "could not load the dynamic library" << std::endl;
				return EXIT_FAILURE;
			}

			// Get function pointer
			getAlgorithmFunc = (getAlgorithmFunc)GetProcAddress(hDll, "GetAlgorithm");
			if(!getAlgorithmFunc)
			{
				std::cout << "could not load function GetAlgorithm()" << std::endl;
				return EXIT_FAILURE;
			}

			dll_vec.push_back(make_tuple(algoName, hDll, getAlgorithmFunc));

		} 
	}
	CommonPlayer* playerA = (*get<2>(dll_vec[0])());
	CommonPlayer* playerB = (*get<2>(dll_vec[1])());
   	

	newGame = new Game();
	initializedSuccessfully = newGame->initGame(argc, argv, playerA, playerB);
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
	// close all the dynamic libs we opened
	for(vitr = dll_vec.begin(); vitr != dll_vec.end(); ++vitr)
	{
		FreeLibrary(get<1>(*vitr));
	}
	return 0;
}
