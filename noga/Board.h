#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Board {
	Point matrix[10][10];
public:
	void loadBoard(const string& boardFile, Player A, Player B);
	Board(){}
	~Board(){delete[] board;}
	AttackResult play_attack(pair <int, int>);

	//not used constructor
	//Board(const string& boardFile);
private:
	int setBoardsToPoint(Point* point, int i, int j, int size, int player, Player A, Player B);

};

#endif
