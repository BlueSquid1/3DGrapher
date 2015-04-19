#ifndef EDITTEXTSTATE_H
#define EDITTEXTSTATE_H

#include "GameStatus.h"

class EditTextState : public GameStatus
{
public:

	//constructor
	EditTextState(mString currentText, int x1, int y1, int x2, int y2);
	bool Input();
	bool Proccess();
	void Display();
};

#endif