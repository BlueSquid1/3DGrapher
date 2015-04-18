#ifndef EVALUATE_H
#define EVALUATE_H



#if _MSC_VER == 1800
	#include <iostream>
#endif

#include "EVALD.h"
#include "mString.h"

class Evaluate
{
public:
	static float Eval(unsigned char * equation, const float& x, const float& y);
	static float Eval(mString equation, const float& x, const float& y);
};

#endif