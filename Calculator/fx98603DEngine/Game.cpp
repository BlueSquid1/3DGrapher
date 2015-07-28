#include "Game.h"


Game::Game(const int& widthRes, const int& heightRes) : gRenderer(widthRes, heightRes), MainMenu(&gRenderer), EditText(&gRenderer), ViewWindow(&gRenderer), Engine3D(&gRenderer, &ViewWindow)
{
	currentState = &MainMenu;
}


bool Game::UpdateCurrentState()
{
	StateType from = currentState->state;
	StateType destiny = currentState->nextState;

	if (from == MAINMENU && destiny == GRAPHER)
	{

		//load the functions
		Engine3D.LoadFunctions(MainMenu.GetFunctions());

		currentState = &Engine3D;

	}

	else if (from == MAINMENU && destiny == VWINDOW)
	{
		currentState = &ViewWindow;
	}
	else if (from == GRAPHER && destiny == MAINMENU)
	{

		currentState = &MainMenu;
	}
	else if (from == VWINDOW && destiny == MAINMENU)
	{
		currentState = &MainMenu;
	}
	else
	{
		//do nothing
	}

	return true;
}

bool Game::RunCurrentState()
{
	currentState->Proccess();

	currentState->Display();

	//ideally would do input first but the casio library pauses the program until user input
	bool mContinue = currentState->Input();

	return mContinue;
}