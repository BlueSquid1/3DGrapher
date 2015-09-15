#ifndef protosdH
#define protosdH
#ifdef __cplusplus
extern "C" {
#endif

void   airy(double x,double *ai,double *aip,double *bi,double *bip);

#ifdef __cplusplus
}
#endif
#endif

#define AUXCONSTS
#define AUXFUNCS

#include <float.h>
#include <math.h>

//
double Lcm(double a, double b){if(fmod(b,a)==0) return a; else return Lcm(fmod(b,a),a);}
double Gcd(double a, double b){return a*b/Lcm(a,b);}
double IIF(double x, double y, double z){if(x!=0) return y; else return z;}
double UnitStep(double t)
{
	if (t >= 0)
	{
		return 1.0;
	}
	else
	{
		return 0.0;
	}
}

double RampFunc(double t)
{
	return t * UnitStep(t);
}

double RectFunc(double t)
{
	if (fabs(t) < 0.5)
	{
		return 1.0;
	}
	else 
	{
		return 0.0;
	}
	return 0.0;
}

double TriangleFunc(double t)
{
	if (fabs(t) < 1.0)
	{
		return 1.0 - fabs(t);
	}
	else
	{
		return 0.0;
	}
	return 0.0;
}

double SignumFunc(double t)
{
	if (t < 0)
	{
		return -1.0;
	}
	else
	{
		return 1.0;
	}
	return 0.0;
}

double SincFunc(double t)
{
	//make sure not dividing by zero
	if (t == 0.0)
	{
		return 1.0;
	}

	float pi = (float)3.1415926535897932;
	return (sin(pi * t)) / (pi*t);
}
//

/*double acos(double);
double asin(double);
double atan(double);
double cos(double);
double sin(double);
double tan(double);
double Sqr(double x){if(x<0) { return DBL_MAX;}; return (pow(x,0.5));}
double log(double);
double log10(double);

#ifndef protosdH
#define protosdH
#ifdef __cplusplus
extern "C" {
#endif

double Acos(double x);
double Acosh(double x);
double Asin(double x);
double Asinh(double x);
double Atan(double x);
double Atan2(double y,double x);
double Atanh(double x);
double Ceil(double x);
double Cos(double x);
double cosdg(double x);
double Cosh(double x);
double Cot(double x);
double Coth(double x);
double Exp(double x);
double Exp10(double x);
double expn(int n,double x);
double Fabs(double x);
double Floor(double x);
double Log(double x);
double log2(double x);
double Log10(double x);
double Sin(double x);
double sindg(double x);
double Sinh(double x);
double Sqrt(double x);
double Tan(double x);
double tandg(double x);
double Tanh(double x);

#ifdef __cplusplus
}
#endif
#endif
*/