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

void Menu::PrintUI()
{
	//print the Fn buttons
	this->selectBut.Render(gRenderer);
	this->drawBut.Render(gRenderer);
	this->VWindowBut.Render(gRenderer);
}


Menu::Menu(Renderer* origRenderer) : GameStatus(origRenderer, MAINMENU)
{
	this->funcSelector = 0;

	//setup buttons
	this->selectBut.SetPos(21 * 0, 7 * 8);
	this->selectBut.SetText("Sel");

	this->drawBut.SetPos(21 * 5, 7 * 8);
	this->drawBut.SetText("Draw");

	this->VWindowBut.SetPos(21 * 2, 7 * 8);
	this->VWindowBut.SetText("VWin");

}

bool Menu::Input()
{
#if _MSC_VER == 1800
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (gRenderer->e.type == SDL_QUIT)
		{
			this->nextState = QUIT;
			return false;
		}
		else if (gRenderer->e.type == SDL_KEYDOWN)
		{
			switch (gRenderer->e.key.keysym.sym)
			{
			case SDLK_RIGHT:
				this->nextState = EDITTEXT;
				return false;
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

			case SDLK_F1:
			{
				//invert the drawablity of current function
				func[funcSelector].SetDrawable(!func[funcSelector].IsDrawable());

				//if function is no longer drawable then delete the grid
				if (!func[funcSelector].IsDrawable())
				{
					func[funcSelector].ClearGrid();
				}
				break;
			}

			case SDLK_F3:
			{
				this->nextState = VWINDOW;
				return false;
				break;
			}

			case SDLK_F6:
			{
				this->nextState = GRAPHER;
				return false;
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
		this->nextState = EDITTEXT;
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
	
	case KEY_CTRL_F1:
	{
		//invert the drawablity of current function
		func[funcSelector].SetDrawable(!func[funcSelector].IsDrawable());

		//if function is no longer drawable then delete the grid
		if (!func[funcSelector].IsDrawable())
		{
			func[funcSelector].ClearGrid();
		}
		break;
	}
	case KEY_CTRL_F3:
	{
		this->nextState = VWINDOW;
		return false;
		break;
	}

	case KEY_CTRL_F6:
	{
		this->nextState = GRAPHER;
		return false;
		break;
	}

	default:
	{
		//if its none of the special case keys then edit the text
		this->nextState = EDITTEXT;
		return false;
		break;
	}
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
	this->PrintUI();
	gRenderer->UpdateScreen();
}

uString& Menu::CurrentString()
{
	return this->func[funcSelector].GetEquation();
}

int Menu::GetFuncNum()
{
	return this->funcSelector;
}

bool Menu::SetCurrentFunction(const uString& text)
{
	func[funcSelector].GetEquation() = text;
	func[funcSelector].SetDrawable(true);
	return true;
}


Function* Menu::GetFunctions()
{
	return func;
}


Menu::~Menu()
{
#if _MSC_VER == 1800
	SDL_Quit();
#endif
}