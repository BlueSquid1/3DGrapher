#ifndef EDITTEXTSTATE_H
#define EDITTEXTSTATE_H

#include "GameStatus.h"
#include "uString.h"
#include "Point.h"

extern "C"
{
	#include <fxlib.h>
	#include <stdio.h>
}

class EditTextState : public GameStatus
{
	uString text;
	
	Point topLeft;
	Point botRight;
public:

	//constructor
	EditTextState(const int& width, const int& height);
	
	bool LoadText(uString& input);
	
	bool LoadPosition(Point& TR, Point& BL);
	
	bool LoadTextAndPos(uString& inputText, Point& TR, Point& BL);
	
	bool Input();
	bool Proccess();
	void Display();
	
	uString& GetText();
};

#endif