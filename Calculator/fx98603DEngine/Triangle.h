#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include "Vector.h"
#include "Renderer.h"

class Triangle
{
	Point P1;
	Point P2;
	Point P3;

	//calculate the next x value on a line with gradient = slope and through point = pos
	static int Interpolate(const int& y, const float& slope, const Point& pos);

public:

	bool SetTriangle(const Point& A, const Point& B, const Point& C);

	//Triangle edges are maps as follows:
	/*

	         P3
	       /  |
  (edge) /    |
	   /      | (hypothysis)
	P2        | 
	   \      |
  (edge)  \   |
		     P1

	*/
	//only draws edges that are set to true.
	void DrawEdges(const Renderer* gRenderer, bool P1toP2 = true, bool P2toP3 = true, bool P3toP1 = true, bool inBlack = true) const;

	void DrawSurface(const Renderer* gRenderer);

	Point GetCenterPoint();
	
	Vector GetNormal();

};

#endif