#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Boat{
	int size;
	Point points [];
	int horizontal;
	int pointsNum;
	int player;
	int hit;
};
public:
	Boat(int size, Point point, int player);
	~Boat();
	int getHorizontal;
	int getPlayer();
	int getPointNum();
	int getSize();
	int isSunk();
	void setHit(int hitPoints);
	void addPoint(Point point);
	void setHorizontal(int horizontal);

private:
	void notifyPlayerSunk();
	void notifyPlayerCreated();

};

#endif