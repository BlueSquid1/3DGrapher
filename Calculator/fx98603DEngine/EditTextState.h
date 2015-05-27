#ifndef EDITTEXTSTATE_H
#define EDITTEXTSTATE_H

#include "GameStatus.h"
#include "uString.h"
#include "Point.h"

extern "C"
{
	#include <stdio.h>
}

class EditTextState : public GameStatus
{
	uString text;
	
	Point topLeft;
	Point botRight;

	int curserPos;

#if _MSC_VER == 1200
	bool EnteredText(unsigned int mKey);
	uString textBuffer;
#endif

public:

	//constructor
	EditTextState(Renderer* gRenderer);
	
	bool LoadText(uString& input);
	
	bool LoadPosition(Point& TR, Point& BL);
	
	bool LoadTextAndPos(uString& inputText, Point& TR, Point& BL);
	
	bool Input();
	bool Proccess();
	void Display();
	
	uString& GetText();
};

#endif