#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Board {
	char board[10][10];
public:
	void getBoard(const string& boardFile);
	Board(){}
	Board(const string& boardFile);
	~Board(){delete[] board;}
};

#endif
