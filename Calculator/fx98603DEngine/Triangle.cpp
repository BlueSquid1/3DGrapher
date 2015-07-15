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


void Triangle::DrawEdges(const Renderer* gRenderer, bool P1toP2, bool P2toP3, bool P3toP1, bool inBlack) const
{
	if (P1toP2)
	{
		gRenderer->DrawLine(P1.x, P1.y, P2.x, P2.y, inBlack);
	}
	if (P2toP3)
	{
		gRenderer->DrawLine(P2.x, P2.y, P3.x, P3.y, inBlack);
	}
	if (P3toP1)
	{
		gRenderer->DrawLine(P3.x, P3.y, P1.x, P1.y, inBlack);
	}
}


void Triangle::DrawSurface(const Renderer* gRenderer)
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

	//find slope between P1 and P2
	float ex = 0.0;
	float sx = 0.0;
	bool horizontalEX = false;
	if (Points[0]->y != Points[1]->y) //avoid dividing by zero
	{
		ex = ((float(Points[1]->x) - float(Points[0]->x)) / (float(Points[1]->y) - float(Points[0]->y)));
	}
	else
	{
		horizontalEX = true;
	}
	
	if (Points[0]->y != Points[2]->y) //avoid dividing by zero
	{
		sx = ((float(Points[2]->x) - float(Points[0]->x)) / (float(Points[2]->y) - float(Points[0]->y)));
	}

	if (!horizontalEX)
	{
		for (int y = Points[0]->y; y < Points[1]->y; y++)
		{
			int x2 = ex * float(y - Points[0]->y) + Points[0]->x;
			int x1 = sx * float(y - Points[0]->y) + Points[0]->x;
			gRenderer->DrawLine(x1, y, x2, y);
		}
	}

	if (Points[1]->y != Points[2]->y) //avoid dividing by zero
	{
		ex = ((float(Points[2]->x) - float(Points[1]->x)) / (float(Points[2]->y) - float(Points[1]->y)));
	}

	for (int y = Points[1]->y; y < Points[2]->y; y++)
	{
		int x2 = ex * float(y - Points[1]->y) + Points[1]->x;
		int x1 = sx * float(y - Points[0]->y) + Points[0]->x;
		gRenderer->DrawLine(x1, y, x2, y);
	}

}


Point Triangle::GetCenterPoint()
{
	Point Centre;
	Centre.x = float(P1.x + P2.x + P3.x)/3.0;
	Centre.y= float(P1.y + P2.y + P3.y) / 3.0;
	Centre.z = float(P1.z + P2.z + P3.z) / 3.0;

	return Centre;
}

Vector Triangle::GetNormal()
{
	//P2 to P1 vector
	int xDir = P1.x - P2.x;
	int yDir = P1.y - P2.y;
	float zDir = P1.z - P2.z;
	Vector sx(xDir, yDir, zDir);

	//P2 to P4 vector
	xDir = P2.x - P3.x;
	yDir = P2.y - P3.y;
	zDir = P2.z - P3.z;
	Vector ex(xDir, yDir, zDir);

	//cross product sx and ex
	xDir = sx(1) * ex(2) - sx(2) * ex(1);
	yDir = sx(2) * ex(0) - sx(0) * ex(2);
	zDir = sx(0) * ex(1) - sx(1) * ex(0);

	Vector cross(xDir, yDir, zDir);

	return cross;
}