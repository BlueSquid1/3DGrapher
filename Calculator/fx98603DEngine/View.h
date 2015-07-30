#ifndef VIEW_H
#define VIEW_H

#include "Object.h"
#include "Vector.h"
#include "Matrix.h"
#include "VWindow.h"
#include "Renderer.h"
#include "Triangle.h"

class View : public Object
{
	Matrix OrthMat;
	Vector rotHist;
	Renderer * gRenderer;
	VWindow * viewWindow;

	float width;
	float height;
	float near;
	float far;
public:
	//constructor
	View(Renderer* origRenderer, VWindow * origViewWindow);
	
	bool RotateGlobal(const float& angdX, const float& angdY, const float& angdZ);

	Vector TransformationCoor(const Vector& vec1);

	//contains the maths behind making 3D spaces
	//vec1 is a vector with 3D info (x, y, z)
	//screenWidth and screenHeight needed to scale the result to fit the screen
	//returns a vector where x,y present the x,y pixels across the screen. z is distance away from screen (used for FOV effects)
	Vector Project3Dto2D(const Vector& vec1);
	Vector OrthProject(const Vector& vec1);

	void DrawLine3D(float x1, float y1, float z1, float x2, float y2, float z2, bool inBlack = true);

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