#include "Board.h"
#include <iostream>
#include <string>
#include <fstream>




Board::Board() :
matrix(NULL){}

Board(const string& boardFile){
	matrix(NULL);
	getBoard(boardFile);
}
getBoard(const string& boardFile)

void Board::getBoard(const string& boardFile) {
	string board[10];
	ifstream fin(boardFile);
	for (int i = 0; i < 10; i++) {
		std::getline(fin, board[i]);
	}

	Point points_matrix[10][10];
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			std::cout << board[i].at(i);
			points_matrix[i][j].setX(i);
			points_matrix[i][j].setY(j);
			if (i>0){
				points_matrix[i][j].setLeft = &points_matrix[i - 1][j];
				points_matrix[i-1][j].setRight = &points_matrix[i][j];
				if (points_matrix[i-1][j].getBoat != NULL){
					points_matrix[i][j].setNear(1);
				}
			}
			if (j>0){
				points_matrix[i][j].setDown = &points_matrix[i][j-1];
				points_matrix[i][j-1].setUp = &points_matrix[i][j];
				if (points_matrix[i][j-1].getBoat != NULL){
					points_matrix[i][j].setNear(1);
				}
			}


			if (cout == 'b'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(1, &points_matrix[i][j],0);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					//error
					return NULL
				}
			}
			if (cout == 'B'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(1, &points_matrix[i][j],1);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					//error
					return NULL
				}
			}
			if (cout == 'p'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(2, &points_matrix[i][j],0);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					if (i > 0){
						Boat boat = points_matrix[i][j].getLeft->getBoat;
						if (boat != NULL){
							if (boat.getSize == 2 && boat.getHorizontal < 2 && boat.getPointsNum < 2 &&boat.getPlayer==0{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(1);
								if (j > 0){
									points_matrix[i][j].getUp->setNear(1);
								}
								
							}
							else{
								//error
								return NULL;
							}
						}
					}
					if (j>0){
						Boat boat = points_matrix[i][j].getUp->getBoat;
						if (boat != NULL){
							if (boat.getSize == 2 && boat.getHorizontal != 1 && boat.getPointsNum < 2 && boat.getPlayer == 0{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(2);
								if (i > 0){
									points_matrix[i][j].getLeft->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}

				}
			}
			if (cout == 'P'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(2, &points_matrix[i][j], 1);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					if (i > 0){
						Boat boat = points_matrix[i][j].getLeft->getBoat;
						if (boat != NULL){
							if (boat.getSize == 2 && boat.getHorizontal < 2 && boat.getPointsNum < 2 && boat.getPlayer == 1{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(1);
								if (j > 0){
									points_matrix[i][j].getUp->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}
					if (j>0){
						Boat boat = points_matrix[i][j].getUp->getBoat;
						if (boat != NULL){
							if (boat.getSize == 2 && boat.getHorizontal != 1 && boat.getPointsNum < 2 && boat.getPlayer == 1{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(2);
								if (i > 0){
									points_matrix[i][j].getLeft->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}

				}

			}
			if (cout == 'm'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(3, &points_matrix[i][j], 0);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					if (i > 0){
						Boat boat = points_matrix[i][j].getLeft->getBoat;
						if (boat != NULL){
							if (boat.getSize == 3 && boat.getHorizontal < 2 && boat.getPointsNum < 3 && boat.getPlayer == 0{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(1);
								if (j > 0){
									points_matrix[i][j].getUp->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}
					if (j>0){
						Boat boat = points_matrix[i][j].getUp->getBoat;
						if (boat != NULL){
							if (boat.getSize == 3 && boat.getHorizontal != 1 && boat.getPointsNum < 3 && boat.getPlayer == 0{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(2);
								if (i > 0){
									points_matrix[i][j].getLeft->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}

				}
			}
			if (cout == 'M'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(3, &points_matrix[i][j], 1);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					if (i > 0){
						Boat boat = points_matrix[i][j].getLeft->getBoat;
						if (boat != NULL){
							if (boat.getSize == 3 && boat.getHorizontal < 2 && boat.getPointsNum < 3 && boat.getPlayer == 1{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(1);
								if (j > 0){
									points_matrix[i][j].getUp->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}
					if (j>0){
						Boat boat = points_matrix[i][j].getUp->getBoat;
						if (boat != NULL){
							if (boat.getSize == 3 && boat.getHorizontal != 1 && boat.getPointsNum < 3 && boat.getPlayer == 1{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(2);
								if (i > 0){
									points_matrix[i][j].getLeft->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}

				}
			}
			if (cout == 'd'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(4, &points_matrix[i][j], 0);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					if (i > 0){
						Boat boat = points_matrix[i][j].getLeft->getBoat;
						if (boat != NULL){
							if (boat.getSize == 4 && boat.getHorizontal < 2 && boat.getPointsNum < 4 && boat.getPlayer == 0{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(1);
								if (j > 0){
									points_matrix[i][j].getUp->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}
					if (j>0){
						Boat boat = points_matrix[i][j].getUp->getBoat;
						if (boat != NULL){
							if (boat.getSize == 4 && boat.getHorizontal != 1 && boat.getPointsNum < 4 && boat.getPlayer == 0{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(2);
								if (i > 0){
									points_matrix[i][j].getLeft->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}

				}
			}
			if (cout == 'D'){
				if (points_matrix[i][j].getNear == 0){
					Boat boat = Boat(4, &points_matrix[i][j], 1);
					points_matrix[i][j].setBoat(boat);
					if (i > 0){
						points_matrix[i][j].getLeft->setNear(1);
					}
					if (j > 0){
						points_matrix[i][j].getUp->setNear(1);
					}
				}
				else{
					if (i > 0){
						Boat boat = points_matrix[i][j].getLeft->getBoat;
						if (boat != NULL){
							if (boat.getSize == 4 && boat.getHorizontal < 2 && boat.getPointsNum < 4 && boat.getPlayer == 1{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(1);
								if (j > 0){
									points_matrix[i][j].getUp->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}
					if (j>0){
						Boat boat = points_matrix[i][j].getUp->getBoat;
						if (boat != NULL){
							if (boat.getSize == 4 && boat.getHorizontal != 1 && boat.getPointsNum < 4 && boat.getPlayer == 1{
								boat.AddPoint(points_matrix[i][j]);
								boat.setHorizontal(2);
								if (i > 0){
									points_matrix[i][j].getLeft->setNear(1);
								}

							}
							else{
								//error
								return NULL;
							}
						}
					}
			}

			if (cout != ' ' && cout != 'b'&& cout != 'B'&& cout != 'p'&& cout != 'P'&& cout != 'm'&& cout != 'M'&& cout != 'd'&& cout != 'D'){
				//error
				return NULL;
			}
		}
	}

	this.matrix = points_matrix[10][10];
}


	void Board::play_attack(pair<int, int>){

	}