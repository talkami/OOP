#include "Game.h"


//empty constructor
Game::Game():
	A (NULL), B(NULL), game_board(NULL), turn=0 {}


//init the game
int Game::initGame(const string adrress){
	//http://stackoverflow.com/questions/19189014/how-do-i-find-files-with-a-specific-extension-in-a-directory-that-is-provided-by


	this.game_board = new Board;
	this.A = new Player;
	this.B = new Player;


}

int Game::playGame(){

}


// private functions

void Game::endGame(){

}
void Game::setNextTurn(AttackResult result){

}



// former functions- DELETE
void Game::switchTurn(){
	if (getTurn == 0){
		this.turn = 1;
	}
	else{
		this.turn = 0;
	}
}


// playing 1 turn
AttackResult Game::play_turn(){
	string next_attack;
	if (getTurn == 0){
		if (A.finished){
			if (B.finished){
				this.endGame();
			}
			return NULL;
		}
		next_attack = A.attack();
	}
	else{
		if (B.finished){
			if (A.finished){
				this.endGame();
			}
			return NULL;
		}
		next_attack = A.attack();
	}

	AttackResult attack_result = this.game_board.play_attack(next_attack);

	if (AttackResult == Sink){
		//who take care of updating the points?
	}
	return attack_result;
}