#ifndef MENU_H
#define MENU_H

#include "GameStatus.h"
#include "Function.h"
#include "mString.h"

class Menu : public GameStatus
{
	Function func[6];
	
	//funcSelector is the function the selector is over
	int funcSelector;
	
	void PrintTitle();
	void PrintFunctions();
	
public:
	//constructor
	Menu(const int& width, const int& height);
	bool Input();
	bool Proccess();
	void Display();
	
	mString CurrentString();
	int GetYPos();
	~Menu();

};

#endif