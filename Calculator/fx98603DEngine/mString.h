#ifndef MSTRING_H
#define MSTRING_H



class mString
{
	unsigned char * text;
	int pos;
	int len;
	
public:
	static void ErrorPrint(unsigned char * errorMessage);
#if _MSC_VER == 1800
	static void ErrorPrint(const char * errorMessage);
#endif
	static int Lenof(unsigned char * array);
	static void NextLinePos(unsigned char length, unsigned char &start, unsigned char &end);
	
	//constructors
	mString();
	mString(unsigned char * mText);
	//deconstructor
	~mString();
	
	
	bool SetText(unsigned char * inputText);
	bool ForceLength(int mLength);
	
	void operator=(const mString& strA);
	
	bool Append(char letter);
	unsigned char * GetText() const;
	int GetLen() const;
};

#endif