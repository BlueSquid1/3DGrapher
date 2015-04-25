#include "..\..\..\Calculator\fx98603DEngine\Grapher.h"

#include "..\..\..\Calculator\fx98603DEngine\Function.h"

#include "..\..\..\Calculator\fx98603DEngine\Renderer.h"

#include "..\..\..\Calculator\fx98603DEngine\Menu.h"

#include <iostream>

int main(int argc, char* args[])
{
	//change resolution here
	Renderer gRenderer(800,600);

	GameStatus * CurrentState;

	Grapher Engine3D(&gRenderer);
	Menu MainMenu(&gRenderer);

	CurrentState = &MainMenu;

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

	bool mContinue = true;
	while (mContinue != NULL)
	{
		mContinue = CurrentState->Input();

		CurrentState->Proccess();

		CurrentState->Display();
	}
	return 0;
}