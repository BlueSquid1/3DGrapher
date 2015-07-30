#include "View.h"


View::View(Renderer* origRenderer, VWindow * origViewWindow) : Object(), OrthMat(4, 4, 0), rotHist()
{
	this->Reset();
	gRenderer = origRenderer;
	viewWindow = origViewWindow;
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

Vector View::Project3Dto2D(const Vector& vec1)
{
	//scale vector (so it fits on the screen neatly)
	Vector temp = vec1;
	temp(0) *= viewWindow->GetSettings().xScaling;
	temp(1) *= viewWindow->GetSettings().yScaling;
	temp(2) *= viewWindow->GetSettings().zScaling;


	//project the 3D object onto a 2d plane
	Vector screen;
	screen = this->TransformationCoor(temp);
	
	//places vector into a space defined by points: (-1,-1,-1) and (1,1,1)
	screen = this->OrthProject(screen);

	//then multiple to the size wanted
	float middleWidth = float(gRenderer->SCREEN_WIDTH) / 2.0;
	screen(0) = screen(0) * middleWidth + middleWidth;

	float middleHeight = float(gRenderer->SCREEN_HEIGHT) / 2.0;
	screen(1) = screen(1) * middleHeight + middleHeight;
	
	screen(2) = screen(2) * middleHeight * 0.1;

	return screen;
}

void View::DrawLine3D(float x1, float y1, float z1, float x2, float y2, float z2, bool inBlack)
{
	//scale vector
	x1 *= viewWindow->GetSettings().xScaling;
	x2 *= viewWindow->GetSettings().xScaling;

	y1 *= viewWindow->GetSettings().yScaling;
	y2 *= viewWindow->GetSettings().yScaling;

	z1 *= viewWindow->GetSettings().zScaling;
	z2 *= viewWindow->GetSettings().zScaling;

	//transform coordinates
	Matrix inv = this->GetInverse();
	float mX1 = inv(0, 0) * x1 + inv(0, 1) * y1 + inv(0, 2) * z1;
	float mY1 = inv(1, 0) * x1 + inv(1, 1) * y1 + inv(1, 2) * z1;
	float mZ1 = inv(2, 0) * x1 + inv(2, 1) * y1 + inv(2, 2) * z1;

	float mX2 = inv(0, 0) * x2 + inv(0, 1) * y2 + inv(0, 2) * z2;
	float mY2 = inv(1, 0) * x2 + inv(1, 1) * y2 + inv(1, 2) * z2;
	float mZ2 = inv(2, 0) * x2 + inv(2, 1) * y2 + inv(2, 2) * z2;

	//place points into a space defined by: (-1,-1,-1) and (1,1,1)
	x1 = OrthMat(0, 0) * mX1 + OrthMat(0, 1) * mY1 + OrthMat(0, 2) * mZ1;
	y1 = OrthMat(1, 0) * mX1 + OrthMat(1, 1) * mY1 + OrthMat(1, 2) * mZ1;
	z1 = OrthMat(2, 0) * mX1 + OrthMat(2, 1) * mY1 + OrthMat(2, 2) * mZ1;

	x2 = OrthMat(0, 0) * mX2 + OrthMat(0, 1) * mY2 + OrthMat(0, 2) * mZ2;
	y2 = OrthMat(1, 0) * mX2 + OrthMat(1, 1) * mY2 + OrthMat(1, 2) * mZ2;
	z2 = OrthMat(2, 0) * mX2 + OrthMat(2, 1) * mY2 + OrthMat(2, 2) * mZ2;

	//multiple to the size wanted
	float middleWidth = float(gRenderer->SCREEN_WIDTH) / 2.0;
	float middleHeight = float(gRenderer->SCREEN_HEIGHT) / 2.0;
	x1 = x1 * middleWidth + middleWidth;
	y1 = y1 * middleHeight + middleHeight;
	z1 = z1 * middleHeight * 0.1;

	x2 = x2 * middleWidth + middleWidth;
	y2 = y2 * middleHeight + middleHeight;
	z2 = z2 * middleHeight * 0.1;

	gRenderer->DrawLine(x1, y1, x2, y2, inBlack);
}

bool View::Reset(int widthRange, int heightRange)
{
	rotHist.SetValues(0,0,1);
	this->ResetMatrix();
	
	//set up the camera so that it uses blenders orientation
	this->RotateGlobal(-90.0, 0.0, 0.0);
	this->ScaleGlobal(1, -1, 1);

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