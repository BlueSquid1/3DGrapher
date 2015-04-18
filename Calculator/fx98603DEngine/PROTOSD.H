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
//
/*double acos(double);
double asin(double);
double atan(double);
double cos(double);
double sin(double);
double tan(double);
double Sqr(double x){if(x<0) { return DBL_MAX;}; return (pow(x,0.5));}
double log(double);
double log10(double);*/

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