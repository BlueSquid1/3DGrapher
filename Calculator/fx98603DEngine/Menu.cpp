#include "Menu.h"

extern "C"
{
	#include <fxlib.h>
	#include <stdio.h>
}

void Menu::PrintTitle()
{
	unsigned char title[] = "Graph Func   :";
	gRenderer.PrintTextXY(0,0, title,0);
	
	unsigned char rangeVar[] = "Z=";
	gRenderer.PrintTextXY(85,0, rangeVar,0);
}

void Menu::PrintFunctions()
{	
	func[2].GetEquation().SetText("X+Y");
	func[2].SetDrawable(true);
	
	for(int i = 0; i < 6; i++)
	{
		//First draw a black box where the selector is
		if (i == this->funcSelector)
		{
			gRenderer.DrawBox(0,(i + 1) * 8, 127, (i+ 1) * 8 + 8, 0);
		}
		
		unsigned char ID[5];
		sprintf((char *)ID, "Z%i",(i + 1));
		
		if(func[i].GetEquation().GetLen() == 0)
		{
			ID[2] = ':';
			ID[3] = 0;
		}
		else
		{
			if(func[i].IsDrawable() == true)
			{
				ID[2] = 0xE5;
				ID[3] = 0xB8; //multi-byte charactor negative "="
				ID[4] = 0;
			}
			else
			{
				ID[2] = '=';
				ID[3] = 0;
			}
		}
		
		gRenderer.PrintTextXY(0,(i + 1) * 8, ID, i == this->funcSelector);
		
		//Print function equation
		
		gRenderer.PrintTextXY(18,(i + 1) * 8, func[i].GetEquation().GetText(), i == this->funcSelector);
	}
}


Menu::Menu(const int& width, const int& height) : GameStatus(width, height, mainMenu)
{
	funcSelector = 0;
}

bool Menu::Input()
{
#if _MSC_VER == 1800
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				break;

			case SDLK_LEFT:
				
				break;

			case SDLK_UP:
			{
				funcSelector--;
				break;
			}
			case SDLK_DOWN:
			{
				funcSelector++;
				break;
			}
			
			case SDLK_EQUALS:
			{
				
				break;
			}

			case SDLK_MINUS:
			{
				
				break;
			}

			default:
				break;
			}
		}
	}
#endif

#if _MSC_VER == 1200
unsigned int key;
GetKey(&key);

	switch (key)
	{
	case KEY_CTRL_RIGHT:
		this->nextState = editText;
		return false;
		break;
	case KEY_CTRL_LEFT:
		
		break;

	case KEY_CTRL_UP:
	{
		funcSelector--;
		break;
	}
	case KEY_CTRL_DOWN:
	{
		funcSelector++;
		break;
	}
			
	case KEY_CHAR_PLUS:
	{
		
		break;
	}
		
	case KEY_CHAR_MINUS:
	{
		
		break;
	}

	default:
		break;
	}
#endif
	return true;
}


bool Menu::Proccess()
{
	//check to see if the function curser isn't invalid
	if(funcSelector < 0)
	{
		funcSelector = 0;
	}
	else if (funcSelector > 5)
	{
		funcSelector = 5;
	}
	
	return true;
}


void Menu::Display()
{
	gRenderer.ClearScreen();
	this->PrintTitle();
	this->PrintFunctions();
	gRenderer.UpdateScreen();
}

mString& Menu::CurrentString()
{
	return func[funcSelector].GetEquation();
}

int Menu::GetYPos()
{
	return (this->funcSelector + 1) * 8;
}

bool Menu::SetCurrentFunction(mString text)
{
	func[funcSelector].GetEquation() = text;
	//func[funcSelector].SetEquation();
	return true;
}


Menu::~Menu()
{
#if _MSC_VER == 1800
	SDL_Quit();
#endif
}