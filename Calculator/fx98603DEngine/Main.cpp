/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

extern "C"
{
	#include <fxlib.h>
}

#include "Grapher.h"
#include "Menu.h"
#include "EditTextState.h"
#include "point.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
extern "C" int AddIn_main(int isAppli, unsigned short OptionNum)
{
	bool quit = false;
	StateType nextState = mainMenu;
	StateType currentState = mainMenu;
	
	//load all the current states
	GameStatus* state;
	
	Menu menu(128, 64);
	Grapher Engine3D(128, 64);
	EditTextState EditText(128, 64);
	
	//loops though game states
	while(!quit)
	{
		if(currentState == mainMenu && nextState == mainMenu)
		{
			//first time setup
			state = &menu;
		}
		else if (nextState == grapher)
		{
			state = &Engine3D;
		}
		else if (currentState == mainMenu && nextState == editText)
		{
			//mString equation = menu.CurrentString();			//BUG ON THIS LINE OF CODE!!!!!!!!!!!!!
			int posY = menu.GetYPos();
			
			Point TR;
			
			TR.x = 0;
			TR.y = posY;
			
			
			Point BL;
			
			BL.x = 127;
			BL.y = posY + 7;
			
			
			EditText.LoadTextAndPos(TR, BL);
			state = &EditText;
		}
		else if (currentState == editText && nextState == mainMenu)
		{
			//mString updatedText = EditText.GetText();
			
			//menu.SetCurrentFunction(updatedText);
			
			state = &menu;
		}
		
		//repeats game state
		bool mContinue = true;
		while (mContinue == true)
		{
			state->Proccess();
			state->Display();
			mContinue = state->Input();


		}
		
		nextState = state->nextState;
		currentState = state->state;
	}
    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
extern "C" int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

