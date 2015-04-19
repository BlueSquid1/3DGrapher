//comment out to make it work on the casio calculator
//---------------------------------------------------

//---------------------------------------------------

#include "Matrix.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // abs()
#include <math.h> // pow()

#include "mString.h" //error prints

#if _MSC_VER == 1800
	#include <iostream>
#endif

float& Matrix::val(const int& y, const int& x)
{
	//check boundaries
	if(y >= this->r || y < 0 || x >= this->c || x < 0)
	{
		unsigned char s[100] = "point outside the matrix";
		//sprintf((char *) s, "(%d,%d) is outside the matrix %d by %d",y,x,this->r, this->c);
		mString::ErrorPrint(s);
		return this->m[0][0];
	}
	return this->m[y][x];
}

float Matrix::valC(const int& y, const int& x) const
{
	//check boundaries
	if(y >= this->r || y < 0 || x >= this->c || x < 0)
	{
		unsigned char s[100] = "point outside the matrix";
		//sprintf((char *) s, "(%d,%d) is outside the matrix %d by %d",y,x,this->r, this->c);
		mString::ErrorPrint(s);
		return this->m[0][0];
	}
	return this->m[y][x];
}


void Matrix::ClearArray()
{
	for(int y = 0; y < this->r; y++)
	{
		delete[] this->m[y];
		this->m[y] = NULL;
	}
	delete[] this->m;
	this->m = NULL;
}

bool Matrix::SetSpace(const int& mRows, const int& mCols)
{
	if(mRows <= 0 || mCols <= 0)
	{
		mString::ErrorPrint("Dimensions are less than 1 for a matrix");
		return false;
	}
	this->r = mRows;
	this->c = mCols;
	
	this->m = new float* [this->r];
	
	//create space for the matrix
	for(int y = 0; y < this->r; y++)
	{
		this->m[y] = new float [this->c];
		
		//check to see if the memory is available
		if(!m[y])
		{
			mString::ErrorPrint("Ran out of space");
			return false;
		}
	}
	return true;
}

float Matrix::Determ(float ** a, const int& n)
{
	float det = 0;
	
	if(n==1) 
	{
		return a[0][0];
	}	 
	else if(n==2) 
	{
		det=(a[0][0]*a[1][1]-a[0][1]*a[1][0]);

		return det;
	} 
	else 
	{
		float ** temp = new float*[n];
		for(int i = 0; i < n; i++)
		{
			temp[i] = new float[n];
		}
		
		for(int p=0;p<n;p++) 
		{
			int h = 0;
			int k = 0;
			for(int i=1;i<n;i++) 
			{
				for(int j=0;j<n;j++) 
				{
					if(j==p) 
					{
						continue;
					}
					temp[h][k] = a[i][j];
					k++;
					if(k==n-1) 
					{
						h++;
						k = 0;
					}
				}
			}
			det=det+a[0][p]*pow(-1,p)*Determ(temp,n-1);
		}
		
		for (int i = 0; i < n; i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
		return det;
	}
}

Matrix Matrix::GenSubMatrix(const int& ay, const int& ax) const
{	
	//check boundaries
	if(ay >= this->r || ay < 0 || ax >= this->c || ax < 0)
	{
		unsigned char s[100] = "point outside the matrix";
		//sprintf((char *) s, "(%d,%d) is outside the matrix %d by %d",ay,ax,this->r, this->c);
		mString::ErrorPrint(s);
		return this->m[0][0];
	}
	
	if(this->r <= 1 || this->c <= 1)
	{
		mString::ErrorPrint("Matrix must be larger than 1 to generate the submatrix");
		return *this;
	}
	
		
	//submatrix is always one row and one column smaller
	int subR = this->r - 1;
	int subC = this->c - 1;
	
	Matrix temp(subR, subC);
	
	int k = 0;
	int l = 0;
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			if(x != ax && y != ay)
			{
				temp.val(k,l) = this->valC(y,x);
				l++;
				if(l >= subC)
				{
					l = 0;
					k++;
				}
			}
		}
	}
	
	//test result
	//because K passes an extra "k++" it might be equal to subR. That is fine.
	if(k > subR || l >= subC)
	{
		mString::ErrorPrint("Failed to generate a submatrix");
		return *this;
	}
	return temp;
}

Matrix Matrix::Identity(const int& n)
{
	Matrix ident(n, n, 0);
	
	for(int x = 0; x < n; x++)
	{
		ident.val(x,x) = 1;
	}
	return ident;
}


Matrix::Matrix(int mRows, int mCols, float initValue)
{	
	this->SetSpace(mRows, mCols);
	
	//set the value of the matrix
	for(int y = 0; y < mRows; y++)
	{
		for(int x = 0; x < mCols; x++)
		{
			this->val(y,x) = initValue;
		}
	}
}

Matrix& Matrix::Set(int mRows, int mCols, float initValue)
{
	//check if values already set
	if(m != NULL)
	{
		this->ClearArray();
	}
	SetSpace(mRows, mCols);
	
	//initalize space
	for(int y = 0; y < mRows; y++)
	{
		for(int x = 0; x < mCols; x++)
		{
			this->val(y,x) = initValue;
		}
	}
	return *this;
}

Matrix::Matrix (const Matrix& matA)
{
	//record dimensions
	this->r = matA.r;
	this->c = matA.c;
	
	//create space
	this->m = new float* [this->r];
	//create space for the matrix
	for(int y = 0; y < this->r; y++)
	{
		this->m[y] = new float [this->c];
		
		if(!m[y])
		{
			mString::ErrorPrint("Ran out of space");
			return;
		}
	}
	
	//deep copy the values
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			this->val(y,x) = matA.valC(y,x);
		}
	}
}

void Matrix::operator=(const Matrix& matA)
{
	if (matA.r != this->r || matA.c != this->c)
	{
		mString::ErrorPrint("can't to assignment. matrices different dimensions");
		return;
	}
	
	//deep copy the values
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			this->val(y,x) = matA.valC(y,x);
		}
	}
}

float& Matrix::operator()(const int& y, const int& x)
{
	return this->val(y,x);
}



Matrix Matrix::operator+(const Matrix& matA) const
{
	//check the rows and columns
	if(this->r != matA.r || this->c != matA.c)
	{
		mString::ErrorPrint("can't add matrices due to different dimensions");
		return *this;
	}
	
	Matrix sum(this->r, this->c);
	
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			sum.val(y,x) = this->valC(y,x) + matA.valC(y,x);
		}
	}
	return sum;
}

Matrix Matrix::operator-(const Matrix& matA) const
{
	//check the rows and columns
	if(this->r != matA.r || this->c != matA.c)
	{
		mString::ErrorPrint("can add matrices due to different dimensions");
		return *this;
	}
	
	//make matA negative
	return *this + (-matA);
}

//unary minus
Matrix Matrix::operator-() const
{
	Matrix unary(this->r, this->c);
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			unary.val(y,x) = 0.0 - this->valC(y,x); //fast way of finding the negative
		}
	}
	return unary;
}

Matrix Matrix::operator*(const Matrix& matA) const
{
	Matrix muli(this->r, matA.c);

	//check the dimensions first
	if (this->c != matA.r)
	{
		mString::ErrorPrint("dimensions are wrong");
		return *this;
	}

	for (int c1 = 0; c1 < this->r; c1++)
	{
		for (int b = 0; b < matA.c; b++)
		{
			float total = 0;
			for (int a = 0; a < this->c; a++)
			{
				total += this->valC(c1,a) * matA.valC(a,b);
			}
			muli.val(c1,b) = total;
		}
	}
	return muli;
}

Matrix Matrix::operator*(const float& valA) const
{
	Matrix multi(this->r, this->c);
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			multi.val(y,x) = valA * this->m[y][x];
		}
	}
	return multi;
	
}

Matrix operator*(const float& valA, const Matrix& matA)
{
	Matrix multi = matA;
	return multi.operator*(valA);
}

Matrix Matrix::operator/(const float& valA) const
{
	return Matrix::operator*(float(1.0)/valA);
}


Matrix& Matrix::operator*=(const Matrix& matA)
{
	//check dimension checks are done is other functions
	*this = this->operator*(matA);
	
	return *this;
}

Matrix Matrix::operator^(const int& valA) const
{
	//check if square matrix
	if(this->c != this->r)
	{
		mString::ErrorPrint("Not a square matrix. can't use powers");
		return *this;
	}
	
	//special case. if to the power of 0 then return the identity matrix
	if( valA == 0)
	{
		return Matrix::Identity(this->c);
	}
	
	//create a matrix to return the result
	Matrix pow = *this;
	
	if (valA < 0)
	{
		//find the inverse before continuing
		pow = pow.Inverse();
	}
	
	//start at 1 because 0 doesn't count
	for(int i = 1; i < abs(valA); i++)
	{
		pow *= pow;
	}
		
	return pow;
}

Matrix Matrix::Trans() const
{	
	Matrix Transpos(this->r, this->c);
	
	//flip the data
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			//deep copy
			Transpos.val(x,y) = this->valC(y,x);
		}
	}
	return Transpos;
}

float Matrix::Det() const
{
	//first test if the matrix is square
	if(this->r != this->c)
	{
		mString::ErrorPrint("Matrix is not square.");
		return 0.0;
	}

	int n = this->c;
	return Determ(this->m, n);
}

Matrix Matrix::Adj() const
{
	//check if matrix is square
	if(this->r != this->c)
	{
		mString::ErrorPrint("Matrix is not square.");
		return *this;
	}
	
	int n = this->c;
	
	//store the cofactor in temp
	Matrix temp(n, n);
		
	for(int y = 0; y < n; y++)
	{
		for(int x = 0; x < n; x++)
		{
			//now need to generate the submatrix from m[][]
			Matrix subMatrix = GenSubMatrix(y, x);
			
			float elementValue = subMatrix.Det();
		
			//work out the sign and store it into temp
			temp(y,x) = pow(-1,x) * pow(-1, y) * elementValue;
		}
	}
		
	//finally find the transpose of the cofactor matrix
	return temp.Trans();
}


Matrix Matrix::Inverse()
{
	/*
	using formula:

	//inverse = 1 / det A * adj A
	*/

	float det = this->Det();

	if(det == 0.0)
	{
		mString::ErrorPrint("Det is 0. can't find inverse matrix");
		return *this;
	}
	
	Matrix inv(this->Rows(),this->Cols());
	
	inv = this->Adj();
	inv = (inv)/float(det);

	return inv;
}

bool Matrix::operator==(const Matrix& matA) const
{
	//first check the dimensions
	if(this->r != matA.Rows() || this->c != matA.Cols())
	{
		return false;
	}
	
	//check the values
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			if(this->valC(y,x) != matA.valC(y,x))
			{
				return false;
			}
		}
	}
	return true;
}

Matrix::~Matrix()
{
	ClearArray();
}

#if _MSC_VER == 1800
void Matrix::Print(const char * msg) const
{
	std::cout << msg << std::endl;
	
	for(int y = 0; y < this->r; y++)
	{
		for(int x = 0; x < this->c; x++)
		{
			std::cout << this->m[y][x] << " ";
		}
		std::cout << "\n";
	}
}
#endif //DUBUG


//mutic functions
//-------------
int Matrix::Rows() const
{
	return this->r;
}

int Matrix::Cols() const
{
	return this->c;
}
//=============