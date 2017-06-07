#pragma once
class Board{
	vector<vector<vector <char> > > board;
    int row, col, depth;
	PlayerBoard* playerABoard;
	PlayerBoard* playerBBoard;
	Logger* logger;
	bool [9] errorArray = {false};
public:
    Board ();
    ~Board ();

    bool initBoard(const std::string& path, Logger* logger);
	bool loadBoard(const std::string& boardFile);

	void addToPlayerBoard(char currentChar, int row, int col, int depth);
	void addBoatToBoard(int row, int col, int depth, int size, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard);
	bool thereIsBoatNearby(int row, int col, int depth);
	PlayerBoard getPlayerBoard (int player);
	void checkAdjacentBoat(Boat* boat, int row, int col, int depth, int size, int direction, int player, PlayerBoard* ownerBoard, PlayerBoard* rivalBoard);
	void checkBoatValidity();
	void mergeBoats(Boat* boat1, Boat* boat2, int direction, PlayerBoard* ownerBoard);
	bool checkBoard();
};