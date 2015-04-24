#include "uString.h"

//string doesn't use renderer.h because then would need to create a renderer for every string


#if _MSC_VER == 1200
	extern "C"
	{
		#include <stdio.h>
		#include <string.h>
		#include <fxlib.h>
	}
#endif

#if _MSC_VER == 1800
	extern "C"
	{
		#include <stdio.h>
	}
#include <iostream>
#endif


#ifndef NULL
	#define NULL 0
#endif

#if _MSC_VER == 1200
void uString::ErrorPrint(const unsigned char * errorMessage)
{
	//draw error Message box
	PopUpWin(5);
	
	//print the writing
	
	//can fit 25 charactors per line.
	//work out how many lines will need to print
	int size = uString::Lenof(errorMessage);
	int linesNo = (size - 1) / 25 + 1;
	int start = 0;
	int end = 0;
	unsigned char lineText[26];
	
	for(int i = 0; i < linesNo - 1; i++)
	{
		//print line
		
		//can fit 25 charactors per line.
		//therefore go from 0 to 24, 25 to 49, etc
		start = i*25;
		end = (i + 1) * 25 - 1;
		memcpy(lineText, errorMessage + start, 25);
		lineText[25] = '\0';
		PrintMini(12,8 + i * 8,lineText, 0);
	}
	
	//print rest of string
	start = (linesNo - 1) * 25;
	end = size - 1;
	
	//clear the array
	memset(lineText, 0, 25);
	
	memcpy(lineText, errorMessage + start, end - start + 1);
	lineText[25] = '\0';
	PrintMini(12,8 + (linesNo - 1) * 8,lineText, 0);
	
	//update display
	Bdisp_PutDisp_DD();
	
	
	//wait until user hits exit
	unsigned int key = 0;
	GetKeyWait(KEYWAIT_HALTON_TIMEROFF, 0, 0, &key);
}
#endif

#if _MSC_VER == 1800
void uString::ErrorPrint(const unsigned char * errorMessage)
{
	std::cerr << errorMessage << "\n";
}
#endif


int uString::Lenof(const unsigned char* s)
{
	int len = 0;
	while(s[len] != '\0')
	{
		len++;
	}
	return len;
}


uString::uString()
{
	this->length = 0;
	this->capacity = 0;
	text = NULL;
}

uString::uString(const unsigned char * s)
{
	this->length = 0;
	this->capacity = 0;
	text = NULL;
	
	this->SetText(s);
}

bool uString::SetText(const unsigned char * inputText)
{
	//first clear the array
	if(text != NULL)
	{
		this->Clear();
	}
	int sizeTemp = uString::Lenof(inputText);
	int capTemp = sizeTemp + 1; //add one for the '\0'
	
	this->text = new unsigned char[capTemp];
	if(!this->text)
	{
		uString::ErrorPrint((unsigned char *)"Ran out of space to create a string");
		return false;
	}
	memcpy(this->text, inputText,sizeTemp);
	
	this->text[sizeTemp] = '\0';
	
	this->length = sizeTemp;
	this->capacity = capTemp;
	return true;
}

bool uString::SetText(const uString& str)
{
	this->operator=(str);
	return true;
}


void uString::operator=(const uString& str)
{
	if (str.GetLen() > 0)
	{
		const unsigned char * s = str.GetText();
		this->SetText(s);
	}
}
void uString::operator=(const unsigned char* s)
{
	this->SetText(s);
}

unsigned char& uString::operator[](int& index)
{
	return this->text[index];
}

void uString::Clear()
{
	if(this->text != NULL)
	{
		delete[] this->text;
		this->text = NULL;
	}
	this->length = 0;
	this->capacity = 0;
}

const unsigned char* uString::GetText() const
{
	return text;
}

int uString::GetLen() const
{
	return this->length;
}

int uString::GetCapacity() const
{
	return this->capacity;
}

uString::~uString()
{
	this->Clear();
}