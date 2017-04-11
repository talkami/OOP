#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Board {
	Point matrix[10][10];
public:
	void loadBoard(const string& boardFile);
	Board(){}
	~Board(){delete[] board;}
	void play_attack(pair <int, int>);

	//not used constructor
	//Board(const string& boardFile);
private:
	int setBoardsToPoint(Point* point, int i, int j, int size, int player);

};

#endif
