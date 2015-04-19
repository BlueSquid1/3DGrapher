#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "Renderer.h"


enum StateType
{
	mainMenu,
	grapher,
	editText
};

class GameStatus
{
protected:
	Renderer gRenderer;
public:
	StateType state;
	StateType nextState;

	//constructor
	GameStatus(const int& width = 128, const int& height = 64, StateType mState = mainMenu);
	virtual bool Input() = 0;
	virtual bool Proccess() = 0;
	virtual void Display() = 0;
};

#endif