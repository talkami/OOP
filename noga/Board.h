#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Board {
	Point matrix[10][10];
public:
	void getBoard(const string& boardFile);
	Board(){}
	Board(const string& boardFile);
	~Board(){delete[] board;}
	void play_attack(pair <int, int>);
};

#endif
