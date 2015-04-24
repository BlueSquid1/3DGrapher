#ifndef VIEW_H
#define VIEW_H

#include "Object.h"
#include "Vector.h"
#include "Matrix.h"

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
	
	bool Rotate(const float& angdX, const float& angdY, const float& angdZ);

	Vector TransformationCoor(const Vector& vec1);

	Vector Project3Dto2D(const Vector& vec1, int screenWidth, int screenHeight);
	Vector OrthProject(const Vector& vec1);
	
	//width is along the x axis
	//height is along the y axis
	//n is the min value on the z axis
	//f is the max value on the z axis
	bool ViewBoundaries(const float& width, const float& height, const float& near, const float& far);

	Vector& GetRotHist();

	bool Zoom(float& percentage);

};

#endif //VIEW_H