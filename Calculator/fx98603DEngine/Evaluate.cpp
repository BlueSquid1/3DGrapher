#include "Evaluate.h"

float Evaluate::Eval(uString& equation, const float& x, const float& y, int* epos)
{
	unsigned char s[400];
	sprintf((char*)s, "(0*((X=(x=%f))+(Y=(y=%f))))+%s\0", x, y, equation.GetText()); //x, y, function

	double result;

	//ecode is if it failed
	int ecode = !EvaluateD((char*)s, &result, epos);
	return float(result);
}