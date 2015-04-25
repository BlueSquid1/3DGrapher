#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "Renderer.h"
#include <iostream>

enum StateType
{
	mainMenu,
	grapher,
	editText
};

class GameStatus
{
protected:
	Renderer* gRenderer;

public:
	StateType state;
	StateType nextState;

	//constructor
	GameStatus(Renderer* origRenderer, StateType mState = mainMenu);
	virtual bool Input() = 0;
	virtual bool Proccess() = 0;
	virtual void Display() = 0;
};

#endif