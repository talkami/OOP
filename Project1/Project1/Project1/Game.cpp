#include "Game.h"

Game::Game(Player A, Player B, Board game_board):
	A (A), B(B), game_board(game_board), turn=0 {}

const string& Person::getName()const {
	return name;
}
int Game::getTurn()const {
	return turn;
}
void Game::switchTurn(){
	if (getTurn == 0){
		this.turn = 1;
	}
	else{
		this.turn = 0;
	}
}
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

	}
	return attack_result;
}
void Game::endGame(){

}
