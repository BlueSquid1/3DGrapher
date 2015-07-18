#include "Evaluate.h"

float Evaluate::Eval(uString& equation, const float& x, const float& y, int* epos)
{
	unsigned char s[400];
	sprintf((char*)s, "(0*((X=(x=%f))+(Y=(y=%f))))+%s\0", x, y, equation.GetText()); //x, y, function

	double result;

	//ecode is if it failed
	int ecode = !EvaluateD((char*)s, &result, epos);

	/*
	switch (ecode)
	{
	case E_SYNTAX:
		uString::ErrorPrint("Syntax Error");
		break;
	case E_UNBALAN:
		uString::ErrorPrint("Unbalanced parenthesis");
		break;
	case E_DIVZERO:
		uString::ErrorPrint("Attempted division by zero");
		break;
	case E_UNKNOWN:
		uString::ErrorPrint("Reference to unknown variable");
		break;
	case E_MAXVARS:
		uString::ErrorPrint("Maximum variables exceeded");
		break;
	case E_BADFUNC:
		uString::ErrorPrint("Unrecognised function");
		break;
	case E_NUMARGS:
		uString::ErrorPrint("Wrong number of arguments to function");
		break;
	case E_NOARG:
		uString::ErrorPrint("Missing an argument to a function");
		break;
	case E_EMPTY:
		uString::ErrorPrint("Empty expression");
		break;
	}
	*/

	return float(result);
}