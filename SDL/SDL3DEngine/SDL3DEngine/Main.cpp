#include "..\..\..\Calculator\fx98603DEngine\Grapher.h"

#include "..\..\..\Calculator\fx98603DEngine\Function.h"

int main(int argc, char* args[])
{
	//change resolution here
	Grapher Engine3D(800,600);
	
	Function eq;

	unsigned char equationS[] = "X^2-Y^2";

	eq.SetEquation(equationS);

	eq.SetDrawable(true);

	eq.SetGridRes(10, 10);

	Vector min(-3,-3,-3);
	Vector max(3, 3, 3);

	eq.UpdateGrid(min, max);

	Engine3D.LoadFunction(&eq);
	
	bool mContinue = true;
	while (mContinue != NULL)
	{
		mContinue = Engine3D.Input();

		Engine3D.Proccess();

		Engine3D.Display();
	}
	
	return 0;
}