#include "Menu.h"

void Menu::PrintTitle()
{
	uString title = "Graph Func   :";
	gRenderer->PrintTextXY(0,0, title,0);
	
	uString rangeVar = "Z=";
	gRenderer->PrintTextXY(85,0, rangeVar,0);
}

void Menu::PrintFunctions()
{	
	for(int i = 0; i < 6; i++)
	{
		//First draw a black box where the selector is
		if (i == this->funcSelector)
		{
			gRenderer->DrawBox(0,(i + 1) * 8, 127, (i+ 1) * 8 + 8, 0);
		}
		
		uString ID;
		ID.ForceLength(5);

		sprintf((char *)ID.GetText(), "Z%i",(i + 1));
		
		if(func[i].GetEquation().GetLen() == 0)
		{
			ID[2] = ':';
			ID[3] = ' ';
		}
		else
		{
			if(func[i].IsDrawable() == true)
			{
				ID[2] = 0xE5;
				ID[3] = 0xB8; //multi-byte charactor negative "="
			}
			else
			{
				ID[2] = '=';
				ID[3] = ' ';
			}
		}
		
		gRenderer->PrintTextXY(0,(i + 1) * 8, ID, i == this->funcSelector);
		
		//Print function equation
		gRenderer->PrintTextXY(18,(i + 1) * 8, func[i].GetEquation(), i == this->funcSelector);
	}
}


Menu::Menu(Renderer* origRenderer) : GameStatus(origRenderer, mainMenu)
{
	funcSelector = 0;
}

bool Menu::Input()
{
#if _MSC_VER == 1800
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (gRenderer->e.type == SDL_QUIT)
		{
			return false;
		}
		else if (gRenderer->e.type == SDL_KEYDOWN)
		{
			switch (gRenderer->e.key.keysym.sym)
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
	gRenderer->ClearScreen();
	this->PrintTitle();
	this->PrintFunctions();
	gRenderer->UpdateScreen();
}

uString& Menu::CurrentString()
{
	return this->func[funcSelector].GetEquation();
}

int Menu::GetYPos()
{
	return (this->funcSelector + 1) * 8;
}

bool Menu::SetCurrentFunction(const uString& text)
{
	func[funcSelector].GetEquation() = text;
	return true;
}


Menu::~Menu()
{
#if _MSC_VER == 1800
	SDL_Quit();
#endif
}