#include "EditTextState.h"

#if _MSC_VER == 1200
bool EditTextState::EnteredText(unsigned int mKey)
{
	//workout if the user it trying to enter text
	bool validText = true;

	if(mKey >= KEY_CHAR_A && mKey <=KEY_CHAR_Z)
	{
		uString temp = "A";
		temp[0] = 'A' + (mKey - KEY_CHAR_A);
		textBuffer = temp;
	}
	else if (mKey >= KEY_CHAR_0 && mKey <= KEY_CHAR_9)
	{
		uString temp = "0";
		temp[0] = '0' + (mKey - KEY_CHAR_0);
		textBuffer = temp;
	}
	else if (mKey == KEY_CHAR_DP)
	{
		textBuffer = ".";
	}
	else if(mKey == KEY_CHAR_PMINUS)
	{
		textBuffer = "-";
	}
	else if(mKey == KEY_CHAR_PLUS)
	{
		textBuffer = "+";
	}
	else if(mKey == KEY_CHAR_MINUS)
	{
		textBuffer = "-";
	}
	else if(mKey == KEY_CHAR_MULT)
	{
		textBuffer = "*";
	}
	else if(mKey == KEY_CHAR_DIV)
	{
		textBuffer = "/";
	}
	else if(mKey == KEY_CHAR_LPAR)
	{
		textBuffer = "(";
	}
	else if(mKey == KEY_CHAR_RPAR)
	{
		textBuffer = ")";
	}
	else if(mKey == KEY_CTRL_XTT)
	{
		textBuffer = "X";
	}
	else if(mKey == KEY_CHAR_LN)
	{
		textBuffer = "Ln(";
	}
	else if(mKey == KEY_CHAR_EXPN)
	{
		textBuffer = "Exp(";
	}
	else if(mKey == KEY_CHAR_LOG)
	{
		textBuffer = "Log(";
	}
	else if(mKey == KEY_CHAR_EXPN10)
	{
		textBuffer = "10^(";
	}
	else if(mKey == KEY_CHAR_SIN)
	{
		textBuffer = "Sin(";
	}
	else if(mKey == KEY_CHAR_COS)
	{
		textBuffer = "Cos(";
	}
	else if(mKey == KEY_CHAR_TAN)
	{
		textBuffer = "Tan(";
	}
	else if(mKey == KEY_CHAR_POW)
	{
		textBuffer = "^(";
	}
	else if(mKey == KEY_CHAR_SQUARE)
	{
		textBuffer = "^2";
	}
	else if(mKey == KEY_CHAR_ROOT)
	{
		textBuffer = "Sqrt(";
	}
	else
	{
		//not text to enter
		validText = false;
	}
	return validText;
}
#endif


EditTextState::EditTextState(Renderer* gRenderer) : GameStatus(gRenderer, EDITTEXT)
{
	curserPos = 0;
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
	
	#if _MSC_VER == 1800
	//tell OS that the program will be requesting text input
	SDL_StartTextInput();
	#endif
	curserPos = 0;
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
			case SDLK_LEFT:
				if (curserPos > 0)
				{
					curserPos--;
				}
				break;
			case SDLK_RIGHT:
				if (curserPos < text.GetLen())
				{
					curserPos++;
				}
				break;
			case SDLK_BACKSPACE:
			{
				if (curserPos > 0)
				{
					if (text.GetLen() == curserPos)
					{
						//deleting from the end of the string
						text.pop_back();
						curserPos--;
					}
					else
					{
						//deleting from the middle of the string
						text.erase(curserPos - 1, 1);
						curserPos--;
					}
				}
				break;
			}
			case SDLK_DELETE:
			{
				if (curserPos < text.GetLen())
				{
					if (curserPos == text.GetLen() - 1)
					{
						//deleting from the end of the string
						text.pop_back();
					}
					else
					{
						//deleting from the middle of the string
						text.erase(curserPos, 1);
					}
				}
				break;
			}

			case SDLK_ESCAPE:
			{
				this->nextState = MAINMENU;
				return false;
				break;
			}
			case SDLK_RETURN:
			{
				this->nextState = MAINMENU;
				return false;
				break;
			}

			default:
				break;
			}
		}
		else if (gRenderer->e.type == SDL_TEXTINPUT)
		{
			//insert into the string
			uString temp = gRenderer->e.text.text;
			text.Insert(curserPos, temp);
			curserPos += temp.GetLen();
		}
	}
#endif

#if _MSC_VER == 1200
unsigned int key;
GetKey(&key);

	switch (key)
	{
	case KEY_CTRL_RIGHT:
		if (curserPos < text.GetLen())
		{
			curserPos++;
		}
		break;
		
	case KEY_CTRL_LEFT:
		if (curserPos > 0)
		{
			curserPos--;
		}
		break;

	case KEY_CTRL_DEL:
	{
		if (curserPos > 0)
		{
			if (text.GetLen() == curserPos)
			{
				//deleting from the end of the string
				text.pop_back();
				curserPos--;
			}
			else
			{
				//deleting from the middle of the string
				text.erase(curserPos - 1, 1);
				curserPos--;
			}
		}
		break;
	}
	case KEY_CTRL_EXE:
	{
		this->nextState = MAINMENU;
		return false;
		break;
	}
	case KEY_CTRL_EXIT:
	{
		this->nextState = MAINMENU;
		return false;
		break;
	}

	default:
		break;
	}

	//textInput
	if(EnteredText(key))
	{
		//insert into the string
		uString temp = textBuffer;
		this->text.Insert(curserPos, temp);
		//move the curse down the number of charactors recently added
		curserPos += temp.GetLen();
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

	gRenderer->PrintTextXY(topLeft.x, topLeft.y, text, 0);
	
	int curserX = topLeft.x + curserPos * gRenderer->fontWidth;
	
	gRenderer->DrawBox(curserX, topLeft.y, curserX + 1, botRight.y, 0);
	
	//gRenderer->DrawBox(curserX, curserY, curserX + 1, curserY + gRenderer->fontHeight * 1.4, 0);

	gRenderer->UpdateScreen();
}



uString& EditTextState::GetText()
{
	#if _MSC_VER == 1800
	//tell OS that program has stopped text input
	SDL_StopTextInput();
	#endif
	return text;
}
