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
	Point();

	//copy constructor
	Point(Vector vecA);

};

#endif