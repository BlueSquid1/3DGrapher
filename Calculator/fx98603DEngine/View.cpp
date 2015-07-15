#include "View.h"


View::View() : Object(), OrthMat(4, 4, 0), rotHist()
{
	this->Reset();
}

bool View::RotateGlobal(const float& angdX, const float& angdY, const float& angdZ)
{
	rotHist(0) += angdX;
	rotHist(1) += angdY;
	rotHist(2) += angdZ;

	Object::RotateGlobal(angdX, angdY, angdZ);
	return true;
}

bool View::ViewBoundaries(const float& width, const float& height, const float& near, const float& far)
{
	this->width = width;
	this->height = height;
	this->near = near;
	this->far = far;
	
	OrthMat(0,0) = 2.0/width;
	OrthMat(1,1) = 2.0/height;
	OrthMat(2,2) = 1.0/(far - near);
	OrthMat(2,3) = -near / (far - near);
	OrthMat(3,3) = 1.0;
	return true;
}


Vector View::TransformationCoor(const Vector& vec1)
{	
	Vector proj;
	proj = this->GetInverse() * vec1;
	return proj;
}

Vector View::OrthProject(const Vector& vec1)
{
	Vector proj;
	proj = OrthMat * vec1;
	return proj;
}

Vector View::Project3Dto2D(const Vector& vec1, int screenWidth, int screenHeight)
{
	//project the 3D object onto a 2d plane
	Vector screen;

	screen = this->TransformationCoor(vec1);

	
	//places vector into a space defined by points: (-1,-1,-1) and (1,1,1)
	screen = this->OrthProject(screen);

	//then multiple to the size wanted
	float middleWidth = float(screenWidth) / 2.0;
	screen(0) = screen(0) * middleWidth + middleWidth;

	float middleHeight = float(screenHeight) / 2.0;
	screen(1) = screen(1) * middleHeight + middleHeight;
	
	screen(2) = screen(2) * middleHeight * 0.1;

	return screen;
}

bool View::Reset(int widthRange, int heightRange)
{
	rotHist.SetValues(0,0,1);
	this->ResetMatrix();
	//set up the camera so that it uses blenders orientation
	this->ScaleGlobal(1, 1, -1);
	this->RotateGlobal(-90.0, 0.0, 0.0);
	this->TranslationGlobal(0, 0, 0);

	int biggerRange = 1;
	if (widthRange > heightRange)
	{
		biggerRange = widthRange;
	}
	else
	{
		biggerRange = heightRange;
	}

	//setup orthogonal matrix
	ViewBoundaries(2 * widthRange, 2 * heightRange, -biggerRange, biggerRange);

	return true;
}

Vector& View::GetRotHist()
{
	return rotHist;
}

bool View::Zoom(float& percentage)
{
	this->ViewBoundaries(this->width * percentage, this->height * percentage, this->near * percentage, this->far * percentage);
	return true;
}