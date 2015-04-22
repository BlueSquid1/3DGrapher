#ifndef EDITTEXTSTATE_H
#define EDITTEXTSTATE_H

#include "GameStatus.h"
#include "mString.h"
#include "Point.h"

class EditTextState : public GameStatus
{
	//mString text;
	
	Point topLeft;
	Point botRight;
public:

	//constructor
	EditTextState(const int& width, const int& height);
	
	//bool LoadText(mString& input);
	
	bool LoadPosition(Point& TR, Point& BL);
	
	bool LoadTextAndPos(Point& TR, Point& BL);
	
	bool Input();
	bool Proccess();
	void Display();
	
	//mString GetText();
};

#endif