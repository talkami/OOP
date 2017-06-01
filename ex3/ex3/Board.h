#pragma once
class Board{
	vector<vector<vector <char> > > board;
    int row, col, depth;
	PlayerBoard playerABoard;
	PlayerBoard playerBBoard;

public:
    Board ();
    ~Board ();

    bool initBoard(const std::string& path);
	bool loadBoard(const std::string& boardFile, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B);

};