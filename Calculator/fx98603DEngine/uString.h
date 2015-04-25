#ifndef USTRING_H
#define USTRING_H


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
	
	//constructors
	uString();
	uString(const char * s, int roughSize = 0);
	uString(const uString& str);
	
	void operator=(const uString& str);
	void operator=(const char* s);
	unsigned char& operator[](const int& index);
	
	const unsigned char* GetText() const;
	
	bool SetText(const char * inputText, int roughSize = 0);

	bool ForceLength(const int& size);
	int GetLen() const;
	int GetCapacity() const;

	//deconstructor
	~uString();
};


#endif