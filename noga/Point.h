#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Point {
	int x;
	int y;
	Boat boat;
	int near; 
	Point* up;
	Point* down;
	Point* left;
	Point* right;
	int hit;
public:
	Point();
	Point(int x, int y, Boat boat = NULL, int near = 0, Point* up= NULL, Point* down= NULL, Point* left = NULL, Point* right= NULL);
	AttackResult attack();
	~Point();
	int getNear();
	void setNear(int near);
	Point* getUp();
	void setUp(Point* point);
	Point* getDown();
	void setDown(Point* point);
	Point* getLeft();
	void setLeft(Point* point);
	Point* getRight();
	void setRight(Point* point);
	Boat getBoat();
	void setBoat(Boat);
};

#endif
