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

bool EditTextState::WriteEnd(const uString& mText)
{
	uString temp = mText;
	this->text.Insert(curserPos, temp);

	//move the curse down the number of charactors recently added
	curserPos += temp.GetLen();
	return true;
}

EditTextState::EditTextState(Renderer* gRenderer) : GameStatus(gRenderer, EDITTEXT)
{
#if _MSC_VER != 1200
	//tell OS that the program will be requesting text input
	SDL_StartTextInput();
#endif

	curserPos = 0;
	curserStart = curserPos;
	buttonState = MAIN_BUT;


	this->xVarBut.SetPos(21 * 0, 7 * 8);
	this->xVarBut.SetText("X");
#if _MSC_VER != 1200
	this->xVarBut.SetTrigger(SDLK_F1);
#endif
#if _MSC_VER == 1200
	this->xVarBut.SetTrigger(KEY_CTRL_F1);
#endif

	
	this->yVarBut.SetPos(21 * 1, 7 * 8);
	this->yVarBut.SetText("Y");
#if _MSC_VER != 1200
	this->yVarBut.SetTrigger(SDLK_F2);
#endif
#if _MSC_VER == 1200
	this->yVarBut.SetTrigger(KEY_CTRL_F2);
#endif
	
	this->FunctBut.SetPos(21 * 3, 7 * 8);
	this->FunctBut.SetText("FUNC");
#if _MSC_VER != 1200
	this->FunctBut.SetTrigger(SDLK_F4);
#endif
#if _MSC_VER == 1200
	this->FunctBut.SetTrigger(KEY_CTRL_F4);
#endif

	this->unitStep.SetPos(21 * 0, 7 * 8);
	this->unitStep.SetText("USTP");
#if _MSC_VER != 1200
	this->unitStep.SetTrigger(SDLK_F1);
#endif
#if _MSC_VER == 1200
	this->unitStep.SetTrigger(KEY_CTRL_F1);
#endif
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
#if _MSC_VER != 1200
	while (SDL_PollEvent(&gRenderer->e) != 0)
	{
		if (proccessAInput(&gRenderer->e) == false)
		{
			return false;
		}
	}
#endif

#if _MSC_VER == 1200
	unsigned int key;
	GetKey(&key);

	if (proccessAInput(&key) == false)
	{
		return false;
	}

#endif
	return true;
}

#if _MSC_VER != 1200
bool EditTextState::proccessAInput(SDL_Event * e)
{
	if (e->type == SDL_QUIT)
	{
		this->nextState = QUIT;
		return false;
	}
	else if (e->type == SDL_KEYDOWN)
	{
		if (buttonState == MAIN_BUT)
		{
			if (xVarBut.HandleEvent(e))
			{
				this->WriteEnd("X");
			}
			else if (yVarBut.HandleEvent(e))
			{
				WriteEnd("Y");
			}
			else if (FunctBut.HandleEvent(e))
			{
				buttonState = FUNCTION_BUT;
			}
		}
		else if (buttonState == FUNCTION_BUT)
		{
			if (unitStep.HandleEvent(e))
			{
				WriteEnd("U(");
			}
		}

		switch (e->key.keysym.sym)
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
			//exit out of submenus before exitting editor
			if (buttonState != MAIN_BUT)
			{
				buttonState = MAIN_BUT;
			}
			else
			{
				this->nextState = MAINMENU;
				return false;
			}
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
		WriteEnd(gRenderer->e.text.text);
	}

	return true;
}
#endif

#if _MSC_VER == 1200
bool EditTextState::proccessAInput(unsigned int * key)
{
	if (buttonState == MAIN_BUT)
	{
		if (xVarBut.HandleEvent(key))
		{
			WriteEnd("X");
		}
		else if (yVarBut.HandleEvent(key))
		{
			WriteEnd("Y");
		}
		else if (FunctBut.HandleEvent(key))
		{
			buttonState = FUNCTION_BUT;
		}
	}
	else if (buttonState == FUNCTION_BUT)
	{
		if (unitStep.HandleEvent(key))
		{
			WriteEnd("U(");
		}
	}

	switch (*key)
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
	case KEY_CTRL_AC:
	{
		text = "";
		curserPos = 0;
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
		//exit out of submenus before exitting editor
		if (buttonState != MAIN_BUT)
		{
			buttonState = MAIN_BUT;
		}
		else
		{
			this->nextState = MAINMENU;
			return false;
		}
		break;
	}

	default:
		break;
	}

	//textInput
	if (EnteredText(*key))
	{
		//insert into the string
		WriteEnd(textBuffer);
	}
	return true;
}
#endif

bool EditTextState::Proccess()
{
	return true;
}

void EditTextState::Display()
{	
	//clear where text go
	gRenderer->ClearScreen(topLeft, botRight);
	
	//clear where buttons go
	Point ButTop;
	ButTop.x = 0;
	ButTop.y = 7 * 8;

	Point ButBot;
	ButBot.x = 127;
	ButBot.y = 63;
	gRenderer->ClearScreen(ButTop, ButBot);
	
	//can fit only 18 charactors on the screen
	int maxLength = 18;

	//update start position
	if (curserPos > curserStart + maxLength)
	{
		//work out how many right steps to take
		int steps = curserPos - (curserStart + maxLength);

		//update start
		curserStart = curserStart + steps;
	}
	else if (curserPos <= curserStart)
	{
		//work out how many left steps to take
		int steps = 0;
		if (curserStart > maxLength)
		{
			steps = -maxLength;
		}
		else
		{
			steps = -curserStart;
		}

		//update start
		curserStart = curserStart + steps;
	}

	int curserDisplayPos = curserPos - curserStart;

	uString displayedText;
	displayedText.ForceLength(19);

	//update text for display
	if (text.GetLen() > 0)
	{
		displayedText = text.Split(curserStart, text.GetLen());
	}
	else
	{
		displayedText = text;
	}

	//draw function
	gRenderer->PrintTextXY(topLeft.x, topLeft.y, displayedText, 0);

	//draw curser
	int curserX = topLeft.x + curserDisplayPos * gRenderer->fontWidth;
	gRenderer->DrawBox(curserX, topLeft.y, curserX + 1, botRight.y, 0);

	//draw buttons
	if (buttonState == MAIN_BUT)
	{
		this->xVarBut.Render(gRenderer);
		this->yVarBut.Render(gRenderer);
		this->FunctBut.Render(gRenderer);
	}
	else if (buttonState == FUNCTION_BUT)
	{
		this->unitStep.Render(gRenderer);
	}

	gRenderer->UpdateScreen();
}



uString& EditTextState::GetText()
{
	#if _MSC_VER != 1200
	//tell OS that program has stopped text input
	SDL_StopTextInput();
	#endif
	return text;
}
