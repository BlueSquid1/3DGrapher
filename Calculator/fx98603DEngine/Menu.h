#ifndef MENU_H
#define MENU_H

#include "GameStatus.h"
#include "Function.h"
#include "uString.h"

extern "C"
{
#if _MSC_VER == 1200
	#include <fxlib.h>
#endif
	#include <stdio.h>
}


class Menu : public GameStatus
{	
	Function func[6];
	//funcSelector is the function the selector is over
	int funcSelector;
	
	void PrintTitle();
	void PrintFunctions();
	
public:
	//constructor
	Menu(Renderer* origRenderer);
	bool Input();
	bool Proccess();
	void Display();
	
	uString& CurrentString();
	int GetFuncNum();
	
	bool SetCurrentFunction(const uString& text);
	~Menu();

};

#endif