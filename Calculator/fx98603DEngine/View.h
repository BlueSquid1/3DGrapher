#ifndef VIEW_H
#define VIEW_H

#include "Object.h"
#include "Vector.h"
#include "Matrix.h"
#include "VWindow.h"

class View : public Object
{
	Matrix OrthMat;
	Vector rotHist;

	float width;
	float height;
	float near;
	float far;
public:
	//constructor
	View();
	
	bool RotateGlobal(const float& angdX, const float& angdY, const float& angdZ);

	Vector TransformationCoor(const Vector& vec1);

	//contains the maths behind making 3D spaces
	//vec1 is a vector with 3D info (x, y, z)
	//screenWidth and screenHeight needed to scale the result to fit the screen
	//returns a vector where x,y present the x,y pixels across the screen. z is distance away from screen (used for FOV effects)
	Vector Project3Dto2D(const Vector& vec1, int screenWidth, int screenHeight, VWindow * viewWindow);
	Vector OrthProject(const Vector& vec1);
	
	//width is along the x axis
	//height is along the y axis
	//n is the min value on the z axis
	//f is the max value on the z axis
	bool ViewBoundaries(const float& width, const float& height, const float& near, const float& far);

	bool Reset(int widthRange = 10, int heightRange = 10);

	Vector& GetRotHist();

	bool Zoom(float& percentage);

};

#endif //VIEW_H