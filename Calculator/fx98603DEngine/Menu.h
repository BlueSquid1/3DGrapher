#ifndef MENU_H
#define MENU_H

#include "GameStatus.h"
#include "Function.h"


class Menu : public GameStatus
{
	Function func[6];
	
	int funcSelector;
	
	
	void PrintTitle();
	void PrintFunctions();
	
public:
	//constructor
	Menu(const int& width, const int& height);
	bool Input();
	bool Proccess();
	void Display();
	
	
	~Menu();

};

#endif