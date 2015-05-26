#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class Point
{

public:

	int x;
	int y;
	int z;

	//constructor
	Point(int mX = 0, int mY = 0, int mZ = 0);

	//copy constructor
	Point(Vector vecA);

};

#endif