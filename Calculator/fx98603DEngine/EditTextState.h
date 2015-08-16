#ifndef EDITTEXTSTATE_H
#define EDITTEXTSTATE_H

#include "GameStatus.h"
#include "uString.h"
#include "Point.h"
#include "ButtonUI.h"

extern "C"
{
	#include <stdio.h>
}

enum ButState
{
	MAIN_BUT,
	FUNCTION_BUT
};

class EditTextState : public GameStatus
{
	uString text;
	
	Point topLeft;
	Point botRight;

	int curserPos;

	//for display purposes only
	//stores where the first curse pos is on the screen
	int curserStart;

	ButState buttonState;
	//MAIN buttons
	ButtonUI xVarBut;
	ButtonUI yVarBut;
	ButtonUI FunctBut;

	//FUNCTION buttons
	ButtonUI unitStep;

#if _MSC_VER == 1200
	bool EnteredText(unsigned int mKey);
	uString textBuffer;
#endif

	//Writes to the end of the string
	bool WriteEnd(const uString& mText);

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