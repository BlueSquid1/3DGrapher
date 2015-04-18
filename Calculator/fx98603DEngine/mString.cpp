#include "mString.h"


extern "C"
{
#if _MSC_VER == 1200
	#include <fxlib.h>
#endif
	#include <stdio.h> //check------------------------------------
	#include <string.h>
}

int mString::Lenof(unsigned char * array)
{
	int i = 0;
	while(array[i] != 0)
	{
		i++;
		if (i > 1000)
		{
			mString::ErrorPrint("Can't find length of char*");
			return -1;
		}
	}
	return i;
}

mString::mString()
{
	text = 0;
	pos = 0;
	len = 0;
}

mString::mString(unsigned char * mText)
{
	mString::mString();
	this->SetText(mText);
}

mString::~mString()
{
	delete[] this->text;
	text = NULL;
}

void mString::NextLinePos(unsigned char length, unsigned char &start, unsigned char &end)
{
	//only move forward one if its NOT the first line
	if(end != 0)
	{
		start = end + 1;
	}
	//check if we have hit the end of the string
	if(start + 24 >= length)
	{
		end = length;
	}
	else
	{
		//shift everything down
		end = start + 24;
	}
}


#if _MSC_VER == 1200
void mString::ErrorPrint(unsigned char * errorMessage)
{
	//draw error Message box
	PopUpWin(5);
	
	//print the writing
	unsigned char start = 0;
	//can fit 25 charactors per line.
	//therefore go from 0 to 24
	unsigned char end = 0;
	unsigned char length = mString::Lenof(errorMessage);
	for(int z = 0; z < 4; z++)
	{
		//works out the new start and end based of the length of the string
		mString::NextLinePos(length, start, end);
	
	
		//make the line so it can be printed
		unsigned char line[26] = {};
		for(int i = 0, j = start; j <=end; i++, j++)
		{
			line[i] = errorMessage[j];
		}
	
		//display the line
		PrintMini(12, 8 + 8 * z, line, 0);
	}
	
	//update display
	Bdisp_PutDisp_DD();
	
	
	//wait until user hits exit------------------------------------MAKE
	unsigned int key = 0;
	GetKeyWait(KEYWAIT_HALTON_TIMEROFF, 0, 0, &key);
}
#endif //_MSC_VER

#if _MSC_VER == 1800
#include <iostream>
void mString::ErrorPrint(unsigned char * errorMessage)
{
	std::cout << errorMessage << std::endl;
}

void mString::ErrorPrint(const char * errorMessage)
{
	std::cout << errorMessage << std::endl;
}
#endif //_MSC_VER


bool mString::SetText(unsigned char * inputText)
{
	//plus one for \0
	int mLen = this->Lenof(inputText);
	if(!this->ForceLength(mLen + 1))
	{
		mString::ErrorPrint("failed to create dynamic memory for a string.\0");
		return false;
	}
	
	for(int i = 0; i < mLen; i++)
	{
		if(!this->Append(inputText[i]))
		{
			return false;
		}
	}
	
	if(pos > mLen)
	{
		mString::ErrorPrint("pos is greater than length");
		return false; 
	}
	//add end of line charactor
	text[pos] = '\0';
	
	if(!text)
	{
		mString::ErrorPrint("didn't seem to copy the text");
		return false;
	}
	
	return true;
}

bool mString::ForceLength(int mLength)
{	
	text = new unsigned char[mLength];
	if(!text)
	{
		mString::ErrorPrint("can't set the length");
		return false;
	}
	//remember the length
	len = mLength;
	return true;
}

bool mString::Append(char letter)
{	
	if(pos < len)
	{
		text[pos] = letter;
		pos++;
		return true;
	}
	mString::ErrorPrint("ran out of space");
	return false;
}

unsigned char * mString::GetText()
{
	return text;
}

int mString::GetLen()
{
	return len;
}