#include "Point.h"

Point::Point(int mX, int mY, int mZ)
{
	this->x = mX;
	this->y = mY;
	this->z = mZ;
}

Point::Point(Vector vecA)
{
	this->x = int(vecA(0));
	this->y = int(vecA(1));
	this->z = int(vecA(2));
}