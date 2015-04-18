#include "Vector.h"

#include "mString.h"

//override the other constructor to force the matrix to be 4 by 1
Vector::Vector() : Matrix(4,1,0)
{
	this->val(3,0) = 1;
}

Vector::Vector(const float& x, const float& y, const float& z) : Matrix(4,1)
{
	SetValues(x,y,z);
}

void Vector::SetValues(const float& x, const float& y, const float& z)
{
	this->val(0, 0) = x;
	this->val(1, 0) = y;
	this->val(2, 0) = z;
	this->val(3, 0) = 1;
}

void Vector::operator=(const Matrix& matA)
{
	for(int i = 0; i < this->Rows(); i++)
	{
		this->val(i,0) = matA.valC(i,0);
	}
}

Vector::~Vector()
{
}