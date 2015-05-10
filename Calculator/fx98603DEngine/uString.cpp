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
void uString::ErrorPrint(const char * errorMessage)
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
void uString::ErrorPrint(const char * errorMessage)
{
	std::cerr << errorMessage << "\n";
}
#endif


int uString::Lenof(const char* s)
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

	this->SetText("");
}

uString::uString(const char * s, int roughSize)
{
	this->length = 0;
	this->capacity = 0;
	text = NULL;
	
	this->SetText(s, roughSize);
}

uString::uString(const uString& str)
{
	this->length = 0;
	this->capacity = 0;
	text = NULL;

	this->operator=(str);

	if (!text)
	{
		uString::ErrorPrint("unable to copy the string with a copy constructor");
		this->SetText("");
	}
}

bool uString::SetText(const char * inputText, int roughSize)
{
	//first clear the array
	if(text != NULL)
	{
		this->Clear();
	}
	int sizeTemp = uString::Lenof(inputText);
	int capTemp = sizeTemp + 1; //add one for the '\0'
	
	if (roughSize != 0)
	{
		if (capTemp > roughSize + 10)
		{
			uString::ErrorPrint("Looping too many times\n");
		}
	}
	this->text = new unsigned char[capTemp];
	if(!this->text)
	{
		uString::ErrorPrint("Ran out of space to create a string");
		return false;
	}

	for (int i = 0; i < sizeTemp; i++)
	{
		this->text[i] = (unsigned char) inputText[i];
	}
	
	this->text[sizeTemp] = '\0';
	
	this->length = sizeTemp;
	this->capacity = capTemp;
	return true;
}


void uString::operator=(const uString& str) //---
{
	if (str.GetLen() >= 0)
	{
		int lengthTemp = str.GetLen();
		int capTemp = lengthTemp + 1;

		ForceLength(capTemp);

		this->length = lengthTemp;
		this->capacity = capTemp;

		memcpy(this->text, str.GetText(), length);
	}
}
void uString::operator=(const char* s)
{
	this->SetText(s);
}

unsigned char& uString::operator[](const int& index)
{
	if (index < 0 || index >= capacity)
	{
		uString::ErrorPrint("element not in string boundaries");
		return text[0];
	}
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

bool uString::erase(int ele, int number)
{
	//first check if erasing inside the array boundaries
	if (ele + number > this->GetLen())
	{
		uString::ErrorPrint("element to erase not in the string's length");
		return false;
	}

	for (int i = ele; i < this->GetLen(); i++)
	{
		//for each element to delete and after to delete
		
		//fill it in with the remaining charactors

		if (i + number < this->GetLen())
		{
			text[i] = text[i + number];
		}
		else
		{
			text[i] = ' ';
		}
	}

	//update length
	this->length = this->length - number;

	return true;
}

bool uString::pop_back()
{
	return this->erase(this->length - 1, 1);
}

const unsigned char* uString::GetText() const
{
	return text;
}


bool uString::ForceLength(const int& size)
{
	if (size <= 0)
	{
		return false;
	}
	if (this->text != NULL)
	{
		this->Clear();
	}

	text = new unsigned char[size];

	if (!text)
	{
		uString::ErrorPrint("Can't change size of string");
		return false;
	}

	length = size - 1;
	capacity = size;

	memset(text, ' ', length);

	text[capacity - 1] = '\0';

	return true;
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