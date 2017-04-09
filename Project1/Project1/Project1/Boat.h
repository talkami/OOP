#ifndef __myproject_Tires_h__
#define __myproject_Tires_h__

class Boat{
	int size;
	int** location;
	int points;
};
public:
	Boat(int size, int** location);
	~Boat();
	int getPoints();

};

#endif