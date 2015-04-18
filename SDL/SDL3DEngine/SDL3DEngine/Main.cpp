#include "..\..\..\Calculator\fx98603DEngine\Grapher.h"

int main(int argc, char* args[])
{
	//change resolution here
	Grapher Engine3D(800,600);
	
	//generate the function
	Vector min(-3,-3,-3);
	Vector max(3, 3, 3);
	unsigned char equationS[] = "X^2-Y^2";
	Engine3D.LoadEquation(equationS, min, max, 10, 10);

	bool mContinue = true;
	while (mContinue != NULL)
	{
		mContinue = Engine3D.Input();

		Engine3D.Proccess();

		Engine3D.Display();
	}

	return 0;
}