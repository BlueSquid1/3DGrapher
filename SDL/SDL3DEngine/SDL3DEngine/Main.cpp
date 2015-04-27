#include "..\..\..\Calculator\fx98603DEngine\Grapher.h"

#include "..\..\..\Calculator\fx98603DEngine\Function.h"

#include "..\..\..\Calculator\fx98603DEngine\Renderer.h"

#include "..\..\..\Calculator\fx98603DEngine\Menu.h"

#include "..\..\..\Calculator\fx98603DEngine\EditTextState.h"

#include <iostream>


int main(int argc, char* args[])
{
	//change resolution here
	Renderer gRenderer(800,600);

	//load gameStates
	Grapher Engine3D(&gRenderer);
	Menu MainMenu(&gRenderer);
	EditTextState EditText(&gRenderer);

	/*
	Function eq;

	uString equationS = "X^2-Y^2";

	eq.SetEquation(equationS);

	eq.SetDrawable(true);

	eq.SetGridRes(10, 10);

	Vector min(-3,-3,-3);
	Vector max(3, 3, 3);

	eq.UpdateGrid(min, max);

	Engine3D.LoadFunction(&eq);
	*/

	GameStatus * CurrentState = &MainMenu;

	bool quit = false;
	while (!quit)
	{

		EditTextState::UpdateState(CurrentState);

		bool mContinue = true;
		while (mContinue == true)
		{
			mContinue = CurrentState->Input();

			CurrentState->Proccess();

			CurrentState->Display();
		}

		if (CurrentState->nextState == QUIT)
		{
			quit = true;
		}

	}
	return 0;
}