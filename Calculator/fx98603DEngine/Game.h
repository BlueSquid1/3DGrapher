#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "Grapher.h"
#include "Menu.h"
#include "EditTextState.h"

//this class is needed so that its functions have access to the different game states.
//originally most of this code was in main.cpp but UpdateCurrentState() needs to know where
//all the state variables are. Putting states in a class solve this issue.
class Game
{
	Renderer gRenderer;
	
	Grapher Engine3D;
	Menu MainMenu;
	EditTextState EditText;

	Function eq;

public:
	GameStatus * currentState;

	//constructor
	Game(const int& widthRes, const int& heightRes);

	//changes currentState to the next approperate state.
	bool UpdateCurrentState();

	//runs the current state if user triggers the state to end then returns false. 
	//otherwise returns true
	bool RunCurrentState();
};

#endif