#include "Evaluate.h"

extern "C"
{
	#include <stdio.h>
}

float Evaluate::Eval(unsigned char * equation, const float& x, const float& y)
{
	unsigned char s[400];
	sprintf((char*)s, "(0*((X=(x=%f))+(Y=(y=%f))))+%s\0", x, y, equation); //x, y, function

	int epos = 0;
	double result;

	//ecode is if it failed
	int ecode = !EvaluateD((char*)s, &result, &epos);
	return float(result);
}


float Evaluate::Eval(mString equation, const float& x, const float& y)
{
	return Evaluate::Eval(equation.GetText(), x, y);
}