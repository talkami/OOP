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

