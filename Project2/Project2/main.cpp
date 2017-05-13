/**/#include "Game.h"

int main(int argc, char* argv[]){
	char x;
	bool initializedSuccessfully, successfulPlay;
	Game* newGame;

	newGame = new Game();
	initializedSuccessfully = newGame->initGame(argc, argv);
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

	return 0;


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
	std::string path("path"); //Here you should take actual folder
	std::string s = "\\*.dll"; // only .dll endings
	dir = FindFirstFileA((path + s).c_str(), &fileData); // Notice: Unicode compatible version of FindFirstFile
	if(dir != INVALID_HANDLE_VALUE) //check if the dir opened successfully
	{
		// test each file suffix and set variables as needed
		do
		{
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

		} while(FindNextFileA(dir, &fileData)); // Notice: Unicode compatible version of FindNextFile
	}
   
	int choice, i; 
	// create a menu of possible shapes to create and let the user make some 
	while(true)
	{
		i = 1;
		for(vitr = dll_vec.begin(); vitr != dll_vec.end(); ++vitr)
		{
			std::cout << i << " - Create " << get<0>(*vitr) << std::endl;
			i++;
		}

		std::cout << i << " - Draw created shapes\n";
		i++; 
		std::cout << i << " - Exit\n"; 
		std::cout << "> "; 

		std::cin >> choice;
		if(choice == i)
		{
			// close all the dynamic libs we opened
			for(vitr = dll_vec.begin(); vitr != dll_vec.end(); ++vitr)
			{
				FreeLibrary(get<1>(*vitr));
			}

			return 1;
		}
		if(choice == i - 1)
		{
			// draw the shapes
			for(sitr=battleship_vec.begin(); sitr!= battleship_vec.end();++sitr)
			{
				(*sitr)->draw();
			}
		}
		if(choice > 0 && choice < i - 1)
		{
			// add the appropriate shape to the shape list
			battleship_vec.push_back(get<2>(dll_vec[choice -1])());
		}
	}

}

/*
#include<stdio.h>
#include <iostream>
#include<windows.h>

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
	char x;
	system("cls");
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hConsole, &ConCurInf);
	for (int i = 0; i < 255; i++) {
		SetConsoleTextAttribute(hConsole, i);
		std::cout << i<<": HELLO WORLD" << std::endl;
	}

	std::cin >> x;

	return 0;

}
*/

