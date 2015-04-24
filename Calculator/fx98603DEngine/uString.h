#ifndef USTRING_H
#define USTRING_H


class uString
{
	unsigned char * text;
	//length of string (not inlcuding end of line charactor)
	int length; //number of characters in use (not including '\0')
	int capacity; //total number of characters the string can hold (including '\0')
	
public:
	static void ErrorPrint(const unsigned char * errorMessage);
	static int Lenof(const unsigned char * s);
	
	//constructors
	uString();
	uString(const unsigned char * s);
	
	void operator=(const uString& str);
	void operator=(const unsigned char* s);
	unsigned char& operator[](int& index);
	void Clear();
	
	const unsigned char* GetText() const;
	
	bool SetText(const unsigned char * inputText);
	bool SetText(const uString& str);
	int GetLen() const;
	int GetCapacity() const;
	
	//deconstructor
	~uString();
};


#endif