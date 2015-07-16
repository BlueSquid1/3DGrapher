#include "Menu.h"

void Menu::PrintTitle()
{
	uString title = "Graph Func   :";
	gRenderer->PrintTextXY(0,0, title,0);
	
	uString rangeVar = "Z=";
	gRenderer->PrintTextXY(85,0, rangeVar,0);
}

void Menu::PrintFunctions(bool drawSelector)
{	
	for(int i = 0; i < 6; i++)
	{
		if (drawSelector == true)
		{
			//First draw a black box where the selector is
			if (i == this->funcSelector)
			{
				gRenderer->DrawBox(0, (i + 1) * 8, 127, (i + 1) * 8 + 8, 0);
			}
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
#if _MSC_VER == 1200
				ID[2] = 0xE5;
				ID[3] = 0xB8; //multi-byte charactor negative "="
#endif
#if _MSC_VER != 1200
				ID[2] = '|';
				ID[3] = ' ';
#endif
			}
			else
			{
				ID[2] = '=';
				ID[3] = ' ';
			}
		}
		
		if (drawSelector == true)
		{
			gRenderer->PrintTextXY(0, (i + 1) * 8, ID, i == this->funcSelector);
		}
		else
		{
			gRenderer->PrintTextXY(0, (i + 1) * 8, ID, 0);
		}
		
		//Print function equation
		if (drawSelector == true)
		{
			gRenderer->PrintTextXY(18, (i + 1) * 8, func[i].GetEquation(), i == this->funcSelector);
		}
		else
		{
			gRenderer->PrintTextXY(18, (i + 1) * 8, func[i].GetEquation(), 0);
		}
	}
}

void Menu::PrintUI()
{
	//print the Fn buttons
	this->selectBut.Render(gRenderer);
	this->drawBut.Render(gRenderer);
	this->VWindowBut.Render(gRenderer);
}


uString Menu::TextInput()
{
	int funcNum = this->GetFuncNum();
	uString text = this->CurrentString();

	Point TL;
	TL.x = 18;
	TL.y = (funcNum + 1) * 8;

	Point BR;
	BR.x = 127;
	BR.y = TL.y + 8;

	EditTextState EditText(this->gRenderer);

	EditText.LoadTextAndPos(text, TL, BR);

	bool mContinue = true;
	while (mContinue == true)
	{
		EditText.Proccess();

		EditText.Display();

		//ideally would do input first but the casio library pauses the program until user input
		mContinue = EditText.Input();
	}

	return EditText.GetText();
}

void Menu::DisplayNoSelector()
{
	gRenderer->ClearScreen();
	this->PrintTitle();
	this->PrintFunctions(false);
	this->PrintUI();
	gRenderer->UpdateScreen();
}

Menu::Menu(Renderer* origRenderer) : GameStatus(origRenderer, MAINMENU)
{
	this->funcSelector = 0;

	//setup buttons
	this->selectBut.SetPos(21 * 0, 7 * 8);
	this->selectBut.SetText("Sel");
#if _MSC_VER != 1200
	this->selectBut.SetTrigger(SDLK_F1);
#endif
#if _MSC_VER == 1200
	this->selectBut.SetTrigger(KEY_CTRL_F1);
#endif

	this->drawBut.SetPos(21 * 5, 7 * 8);
	this->drawBut.SetText("Draw");
#if _MSC_VER != 1200
	this->drawBut.SetTrigger(SDLK_F6);
#endif
#if _MSC_VER == 1200
	this->drawBut.SetTrigger(KEY_CTRL_F6);
#endif

	this->VWindowBut.SetPos(21 * 2, 7 * 8);
	this->VWindowBut.SetText("VWin");
#if _MSC_VER != 1200
	this->VWindowBut.SetTrigger(SDLK_F3);
#endif
#if _MSC_VER == 1200
	this->VWindowBut.SetTrigger(KEY_CTRL_F3);
#endif
}

bool Menu::Input()
{
#if _MSC_VER != 1200
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (gRenderer->e.type == SDL_QUIT)
		{
			this->nextState = QUIT;
			return false;
		}
		else if (gRenderer->e.type == SDL_KEYDOWN)
		{
			if (selectBut.HandleEvent(&gRenderer->e))
			{
				func[funcSelector].SetDrawable(!func[funcSelector].IsDrawable());

				//if function is no longer drawable then delete the grid
				if (!func[funcSelector].IsDrawable())
				{
					func[funcSelector].ClearGrid();
				}
			}
			else if (VWindowBut.HandleEvent(&gRenderer->e))
			{
				this->nextState = VWINDOW;
				return false;
			}
			else if (drawBut.HandleEvent(&gRenderer->e))
			{
				this->nextState = GRAPHER;
				return false;
			}
			else
			{
				switch (gRenderer->e.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					this->DisplayNoSelector();
					uString text = this->TextInput();
					this->SetCurrentFunction(text);
					break;
				}
				case SDLK_LEFT:
				{
					break;
				}
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

				default:
					break;
				}
			}
		}
	}
#endif

#if _MSC_VER == 1200
	unsigned int key;
	GetKey(&key);
	if (selectBut.HandleEvent(&key))
	{
		func[funcSelector].SetDrawable(!func[funcSelector].IsDrawable());

		//if function is no longer drawable then delete the grid
		if (!func[funcSelector].IsDrawable())
		{
			func[funcSelector].ClearGrid();
		}
	}
	else if (VWindowBut.HandleEvent(&key))
	{
		this->nextState = VWINDOW;
		return false;
	}
	else if (drawBut.HandleEvent(&key))	
	{
		this->nextState = GRAPHER;
		return false;
	}
	else
	{
		switch (key)
		{
		case KEY_CTRL_RIGHT:
		{
			this->DisplayNoSelector();
			uString text = this->TextInput();
			this->SetCurrentFunction(text);
			break;
		}
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

		default:
		{
			//if its none of the special case keys then edit the text
			this->DisplayNoSelector();
			uString text = this->TextInput();
			this->SetCurrentFunction(text);
			break;
		}
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
#if _MSC_VER != 1200
	SDL_Quit();
#endif
}