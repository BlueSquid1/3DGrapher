#include "Point.h"

Point::Point()
{

}

Point::Point(Vector vecA)
{
	this->x = int(vecA(0));
	this->y = int(vecA(1));
	this->z = int(vecA(2));
}