#ifndef EVALUATE_H
#define EVALUATE_H



#if _MSC_VER == 1800
	#include <iostream>
#endif

extern "C"
{
	#include <stdio.h>
}

#include "EVALD.h"
#include "uString.h"

class Evaluate
{
public:
	static float Eval(unsigned char * equation, const float& x, const float& y);
	static float Eval(uString equation, const float& x, const float& y);
};

#endif