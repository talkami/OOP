#pragma once
class Board{
	vector<vector<vector <char> > > board;
    int row, col, depth;
	vector<vector<vector <char> > > playerABoard;
	vector<vector<vector <char> > > playerBBoard;
	Logger* logger;

public:
    Board ();
    ~Board ();

    bool initBoard(const std::string& path, Logger* logger);
	bool loadBoard(const std::string& boardFile, IBattleshipGameAlgo* A, IBattleshipGameAlgo* B);

};