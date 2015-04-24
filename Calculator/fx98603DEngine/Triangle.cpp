#include "Triangle.h"

int Triangle::Interpolate(const int& y, const float& slope, const Point& point)
{
	//using the formula (line formula rearrange for x)
	// x = (dx/dy)*y + (x1-(dx/dy)*y1)
	float constant = point.x - slope * point.y;
	return slope * y + constant;
}


bool Triangle::SetTriangle(const Point& A, const Point& B, const Point& C)
{
	P1 = A;
	P2 = B;
	P3 = C;
	return true;
}


void Triangle::DrawEdges(const Renderer& gRenderer, bool P1toP2, bool P2toP3, bool P3toP1) const
{
	if (P1toP2)
	{
		gRenderer.DrawLine(P1.x, P1.y, P2.x, P2.y);
	}
	if (P2toP3)
	{
		gRenderer.DrawLine(P2.x, P2.y, P3.x, P3.y);
	}
	if (P3toP1)
	{
		gRenderer.DrawLine(P3.x, P3.y, P1.x, P1.y);
	}
}



void Triangle::DrawSurface(const Renderer& gRenderer)
{
	//first sort triangles by y value
	Point* Points[3];
	Points[0] = &P1;
	Points[1] = &P2;
	Points[2] = &P3;

	//sort vectors via y values
	for (int i = 0; i < 2; i++)
	{
		int min = i;
		for (int j = i; j < 3; j++)
		{
			if (Points[j]->y <= Points[min]->y)
			{
				min = j;
			}
		}
		Point* temp = Points[i];
		Points[i] = Points[min];
		Points[min] = temp;
	}


	//find INVERSE slope between P1 and P2
	float ex;
	bool horizontalEX = false;
	if (Points[0]->y != Points[1]->y) //avoid dividing by zero
	{
		ex = ((float(Points[1]->x) - float(Points[0]->x) / float(Points[1]->y) - float(Points[0]->y)));
	}
	else
	{
		//dealing with a horizontal line
		horizontalEX = true;
	}

	int sx;
	bool horizontalSX = false;
	if (Points[2]->y != Points[0]->y)
	{
		sx = ((float(Points[2]->x) - float(Points[0]->x) / float(Points[2]->y) - float(Points[0]->y)));
	}
	else
	{
		horizontalSX = true;
	}
	/*
	int y1 = (*Points)[0].y - 1;
	int x1 = (*Points)[0].x;
	if (!horizontalEX)
	{
		 x1 = Triangle::Interpolate(y1, ex, (*Points)[0]);
	}

	int y2 = (*Points)[0].y - 1;
	int x2 = (*Points)[0].x;
	if (!horizontalSX)
	{
		x2 = Triangle::Interpolate(y2, sx, (*Points)[0]);
	}

	gRenderer.DrawLine((*Points)[0].x, (*Points)[0].y, (*Points)[1].x, (*Points)[1].y);

	std::cout << "origional point: x=" << (*Points)[0].x << " y=" << (*Points)[0].y << std::endl;
	std::cout << "slope = " << ex << std::endl;
	std::cout << "Point1: x=" << x1 << " y=" << y1 << std::endl;

	std::cout << "Point2: x=" << x2 << " y=" << y2 << std::endl;

	//gRenderer.DrawLine(x1, y1, x2, y2);
	*/
}