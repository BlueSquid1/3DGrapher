#include "EditTextState.h"

EditTextState::EditTextState(Renderer* gRenderer) : GameStatus(gRenderer, editText)
{
}


bool EditTextState::LoadText(uString& input)
{
	//delete the previous string
	if(this->text.GetLen() != 0)
	{
		this->text = "";
	}
	this->text = input;
	
	return true;
}
	
bool EditTextState::LoadPosition(Point& TR, Point& BL)
{
	this->topLeft.x = TR.x;
	this->topLeft.y = TR.y;
	
	this->botRight.x = BL.x;
	this->botRight.y = BL.y;
	return true;
}
	
bool EditTextState::LoadTextAndPos(uString& inputText, Point& TR, Point& BL)
{
	this->LoadText(inputText);
	this->LoadPosition(TR, BL);
	return true;
}

bool EditTextState::Input()
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
				
				break;
			}
			case SDLK_DOWN:
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
		
		break;
	case KEY_CTRL_LEFT:
		
		break;

	case KEY_CTRL_UP:
	{
		
		break;
	}
	case KEY_CTRL_DOWN:
	{
		
		break;
	}
	case KEY_CTRL_EXE:
	{
		this->nextState = mainMenu;
		return false;
		break;
	}
	case KEY_CTRL_EXIT:
	{
		this->nextState = mainMenu;
		return false;
		break;
	}

	default:
		break;
	}
#endif
	return true;
}

bool EditTextState::Proccess()
{
	
	return true;
}

void EditTextState::Display()
{	
	gRenderer->ClearScreen(topLeft, botRight);
	
	//gRenderer.PrintTextXY(18,topLeft.y, text.GetText(), 0);
	
	gRenderer->UpdateScreen();
}



uString& EditTextState::GetText()
{
	return text;
}
