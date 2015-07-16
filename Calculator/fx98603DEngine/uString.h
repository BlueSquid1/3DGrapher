#ifndef USTRING_H
#define USTRING_H

extern "C"
{
#if _MSC_VER == 1200
#include <fxlib.h>
#endif

#if _MSC_VER != 1200
#include <stdio.h>
#endif
}

class uString
{
	unsigned char * text;
	//length of string (not inlcuding end of line charactor)
	int length; //number of characters in use (not including '\0')
	int capacity; //total number of characters the string can hold (including '\0')
	
	void Clear();

public:
	static void ErrorPrint(const char * errorMessage);
	static int Lenof(const char * s);
	static int ConvertToInt(uString& sValue);
	static float ConvertToFloat(uString& sValue);

	
	//constructors
	uString();
	uString(const char * s, int roughSize = 0);
	uString(const uString& str);
	
	void operator=(const uString& str);
	void operator=(const char* s);
	unsigned char& operator[](const int& index);
	
	//erase elements in the string
	//ele is the position of the first element to delete
	//number is the number of elements from ele to delete
	//e.g. ele = 3 number = 2 would delete elements 3,4
	bool erase(int ele, int number);

	//insert string at ele
	bool Insert(int ele, uString& mText);

	//erase last element from the string
	bool pop_back();

	const unsigned char* GetText() const;
	
	bool SetText(const char * inputText, int roughSize = 0);

	bool ForceLength(const int& size);
	int GetLen() const;
	int GetCapacity() const;

	//deconstructor
	~uString();
};


#endif