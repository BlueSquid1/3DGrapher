#ifndef FUNCTION_H
#define FUNCTION_H

#include "uString.h"
#include "Vector.h"
#include "Mesh.h"
#include "Evaluate.h"

class Function
{
	//doesn't include "z="
	uString equation;
	bool drawable;
	
	int Xgrid;
	int Ygrid;
	
	Vector lowerBoundary;
	Vector UpperBoundary;

	Mesh object;

public:
	
	//constructors
	Function();
	//x and y change the resolution of the grid
	
	bool SetGridRes(int x, int y);
	void ClearGrid();


	bool SetEquation(uString& text);
	uString& GetEquation();
	
	bool UpdateGrid(Vector& min, Vector& max);
	int GetGrid(const int& x, const int& y);

	int CalculateSpaceRequired(int x, int y);

	Mesh& GetObject();

	void SetDrawable(bool state);
	
	bool IsDrawable();
	
	Vector GetLowerBoundary();
	Vector GetUpperBoundary();

};

#endif