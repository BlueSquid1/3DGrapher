#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(float initValue) : Matrix(0, 0)
{
	m = mainArr;
	m[0] = mem0;
	m[1] = mem1;
	m[2] = mem2;
	m[3] = mem3;

	this->r = 4;
	this->c = 4;

	//set the value of the matrix
	for (int y = 0; y < this->r; y++)
	{
		for (int x = 0; x < this->c; x++)
		{
			this->val(y, x) = initValue;
		}
	}
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matA) const
{
	Matrix4x4 muli;

	for (int c1 = 0; c1 < this->r; c1++)
	{
		for (int b = 0; b < matA.c; b++)
		{
			float total = 0;
			for (int a = 0; a < this->c; a++)
			{
				total += this->valC(c1, a) * matA.valC(a, b);
			}
			muli(c1, b) = total;
		}
	}

	return muli;

}

Matrix4x4 Matrix4x4::operator*(const Vector& matA) const
{
	Matrix4x4 muli;
	//check the dimensions first
	if (this->c != matA.r)
	{
		uString::ErrorPrint("dimensions are wrong");
		return *this;
	}

	for (int c1 = 0; c1 < this->r; c1++)
	{
		for (int b = 0; b < matA.c; b++)
		{
			float total = 0;
			for (int a = 0; a < this->c; a++)
			{
				total += this->valC(c1, a) * matA.valC(a, b);
			}
			muli.val(c1, b) = total;
		}
	}

	return muli;
}

Matrix4x4 Matrix4x4::Inverse()
{
	Matrix4x4 muli;
	return muli;
}

Matrix4x4::~Matrix4x4()
{

}