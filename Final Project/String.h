#ifndef STRING_H
#define STRING_H

#include <iostream>

class String
{
private:
	char* _string;
	int _size;

	int GetLength(const char* string) const;
	int GetLength(const int number) const;
	void CopyString(char* destination, const char* source) const;
	bool IsDelimiter(char c, const char* delim) const;
	bool IsStringFound(int startIndex, const String& s) const;

public:
	String();
	String(char c);
	String(const char* string);
	String(int count, char c);
	String(int number);
	String(const String& other);

	~String();

	void ReplaceFirst(char c);
	int Length() const;
	void Print() const;

	bool IsEqual(const String& other) const;
	bool IsLess(const String& other) const;
	bool IsGreater(const String& other) const;

	int StringToInteger() const;

	String& Trim();
	String* Split(char delim, int& count) const;
	String* Tokenize(const char* delim, int& count) const;
	String Concat(const String& s2) const;
	String& Append(const String& s2);
	int* AllSubStrings(int& count) const;

	const char* Data() const;
	int FindFirst(char ch) const;
	int FindFirst(const String& s) const;
	int FindLast(char ch) const;
	int FindLast(const String& s) const;
	int* FindAll(char ch, int& count) const;
	int* FindAll(const String& s, int& count) const;

	void RemoveAt(int index);
	void InsertAt(int index, char c);
	void InsertAt(int index, const String& s);

	void RemoveFirst(char ch);
	void RemoveLast(char ch);
	void RemoveAll(char ch);

	void Clear();

	String& ToUpper();
	String& ToLower();
	String& Reverse();

	String SubString(int start, int length) const;
	bool StartsWith(const String& s) const;
	bool EndsWith(const String& s) const;
	bool Contains(const String& s) const;
	bool Contains(char ch) const;

	void ReplaceFirst(char from, char to);
	void ReplaceLast(char from, char to);
	void ReplaceAll(char from, char to);
	void ReplaceFirst(const String& from, const String& to);
	void ReplaceLast(const String& from, const String& to);
	void ReplaceAll(const String& from, const String& to);

	String& PadLeft(int totalWidth, char padChar = ' ');
	String& PadRight(int totalWidth, char padChar = ' ');

	bool IsEmpty() const;
	bool IsAlpha() const;
	bool IsNumeric() const;
	bool IsAlphaNumeric() const;

	static int StringToInteger(const String s);
	static String IntegerToString(int num);
	static String Trim(const String& s);
	static String ToUpper(String& s);
	static String ToLower(String& s);
	static String Reverse(String& s);

	String& operator= (const String& other);
	bool operator== (const String& other) const;
	bool operator!= (const String& other) const;
	bool operator<  (const String& other) const;
	bool operator>  (const String& other) const;
	bool operator<= (const String& other) const;
	bool operator>= (const String& other) const;
	String operator+ (const String& other) const;
	String& operator+= (const String& other);
	char operator[] (int i) const;
	char& operator[] (int i);

	friend std::ostream& operator<< (std::ostream& os, const String& s);
	friend std::istream& operator>> (std::istream& is, String& s);
};

#endif // !STRING_H
