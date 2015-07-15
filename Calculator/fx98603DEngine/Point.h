#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class Point
{

public:

	int x;
	int y;
	float z;

	//constructor
	Point(int mX = 0, int mY = 0, float mZ = 0.0); //depth is too small for an int

	//copy constructor
	Point(Vector vecA);

};

#endif