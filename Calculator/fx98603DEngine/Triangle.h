#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
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

	void DrawEdges(const Renderer& gRenderer, bool P1toP2 = true, bool P2toP3 = true, bool P3toP1 = true) const;

	void DrawSurface(const Renderer& gRenderer);
	
};

#endif