#include "String.h"
#include <iostream>

int String::GetLength(const char* string) const
{
	int length = 0;
	while (string[length] != '\0')
		length++;

	return length;
}
int String::GetLength(const int number) const
{
	if (number == 0) return 1;

	int length = 0;
	int temp = (number < 0) ? -number : number;
	while (temp != 0)
	{
		temp /= 10;
		length++;
	}

	return (number < 0) ? length + 1 : length;
}
void String::CopyString(char* destination, const char* source) const
{
	int i = 0;
	while (source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}

	destination[i] = '\0';
}
bool String::IsDelimiter(char c, const char* delim) const
{
	for (int i = 0; delim[i] != '\0'; i++)
	{
		if (c == delim[i])
			return true;
	}

	return false;
}
bool String::IsStringFound(int startIndex, const String& s) const
{
	for (int i = 0; i < s._size; i++)
	{
		if (_string[startIndex + i] != s._string[i])
			return false;
	}

	return true;
}

String::String() : _size(0)
{
	_string = new char[1];
	_string[0] = '\0';
}
String::String(char c) : _size(1)
{
	_string = new char[2];
	_string[0] = c;
	_string[1] = '\0';
}
String::String(const char* string) : _size(GetLength(string))
{
	_string = new char[_size + 1];
	CopyString(_string, string);
}
String::String(int count, char c) : _size(count)
{
	if (count < 0) throw "String count parameter cannot be negative.";

	_string = new char[_size + 1];

	for (int i = 0; i < _size; i++)
		_string[i] = c;
	_string[_size] = '\0';
}
String::String(int number) : _size(0)
{
	_string = new char[1];
	_string[0] = '\0';
	*this = IntegerToString(number);
}
String::String(const String& other) : _size(other._size)
{
	_string = new char[_size + 1];
	CopyString(_string, other._string);
}

String::~String()
{
	delete[] _string;
}

void String::ReplaceFirst(char c) { if (_size > 0) _string[0] = c; }
int String::Length() const { return _size; }
void String::Print() const { std::cout << _string << '\n'; }

bool String::IsEqual(const String& other) const
{
	if (_size != other._size) return false;

	for (int i = 0; i < _size; i++)
	{
		if (_string[i] != other._string[i])
			return false;
	}

	return true;
}
bool String::IsLess(const String& other) const
{
	int minSize = (_size < other._size) ? _size : other._size;

	for (int i = 0; i < minSize; i++)
	{
		if (_string[i] < other._string[i]) return true;
		else if (_string[i] > other._string[i]) return false;
	}

	return _size < other._size;
}
bool String::IsGreater(const String& other) const
{
	int minSize = (_size < other._size) ? _size : other._size;

	for (int i = 0; i < minSize; i++)
	{
		if (_string[i] > other._string[i]) return true;
		else if (_string[i] < other._string[i]) return false;
	}

	return _size > other._size;
}

int String::StringToInteger() const
{
	if (_size == 0) return 0;

	int res = 0;
	int start = 0;
	bool negative = false;

	if (_string[0] == '-')
	{
		negative = true;
		start = 1;
	}

	for (int i = start; i < _size; i++)
	{
		if (_string[i] >= '0' && _string[i] <= '9')
			res = res * 10 + (_string[i] - '0');
	}

	return negative ? -res : res;
}

String& String::Trim()
{
	if (_size == 0) return *this;

	int start = 0;
	while (start < _size && (_string[start] == ' ' || _string[start] == '\t' || _string[start] == '\n'))
		start++;

	int end = _size - 1;
	while (end > start && (_string[end] == ' ' || _string[end] == '\t' || _string[end] == '\n'))
		end--;

	int newSize = (start > end) ? 0 : (end - start + 1);
	char* newString = new char[newSize + 1];

	for (int i = 0; i < newSize; i++)
		newString[i] = _string[start + i];
	newString[newSize] = '\0';

	delete[] _string;
	_string = newString;
	_size = newSize;

	return *this;
}
String* String::Split(char delim, int& count) const
{
	if (_size == 0)
	{
		count = 0;
		return nullptr;
	}

	int parts = 1;
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] == delim && (i + 1) < _size && _string[i + 1] != delim)
			parts++;
	}
	count = parts;

	String* result = new String[count];

	int currentPart = 0;
	int start = 0;
	for (int i = 0; i <= _size; i++)
	{
		if (_string[i] != delim && _string[i] != '\0') continue;

		int partLength = i - start;

		char* temp = new char[partLength + 1];
		for (int j = 0; j < partLength; j++)
			temp[j] = _string[start + j];
		temp[partLength] = '\0';

		result[currentPart++] = String(temp);

		delete[] temp;
		start = i + 1;
	}

	return result;
}
String* String::Tokenize(const char* delim, int& count) const
{
	if (delim == nullptr)
		throw "Delimiter array pointer cannot be null.";

	if (_size == 0)
	{
		count = 0;
		return nullptr;
	}

	int tokens = 0;
	bool inToken = false;
	for (int i = 0; i < _size; i++)
	{
		if (!IsDelimiter(_string[i], delim))
		{
			if (!inToken)
			{
				tokens++;
				inToken = true;
			}
		}
		else inToken = false;
	}

	count = tokens;
	if (count == 0) return nullptr;

	String* result = new String[count];
	int currentToken = 0;
	int tokenStart = -1;
	for (int i = 0; i <= _size; i++)
	{
		if (i != _size && !IsDelimiter(_string[i], delim))
		{
			if (tokenStart == -1) tokenStart = i;
		}
		else if (tokenStart != -1)
		{
			int length = i - tokenStart;
			char* temp = new char[length + 1];

			for (int j = 0; j < length; j++)
				temp[j] = _string[tokenStart + j];
			temp[length] = '\0';

			result[currentToken++] = String(temp);
			delete[] temp;

			tokenStart = -1;
		}
	}

	return result;
}
String String::Concat(const String& s2) const
{
	String result;
	result._size = _size + s2._size;

	delete[] result._string;
	result._string = new char[result._size + 1];

	CopyString(result._string, _string);
	CopyString(result._string + _size, s2._string);

	return result;
}
String& String::Append(const String& s2)
{
	char* newString = new char[_size + s2._size + 1];
	CopyString(newString, _string);
	CopyString(newString + _size, s2._string);

	delete[] _string;
	_string = newString;
	_size += s2._size;

	return *this;
}
int* String::AllSubStrings(int& count) const
{
	count = _size * (_size + 1) / 2;

	if (count == 0) return nullptr;

	int* result = new int[count];
	int index = 0;

	for (int i = 0; i < _size; i++)
	{
		for (int j = i; j < _size; j++)
			result[index++] = j - i + 1;
	}

	return result;
}

const char* String::Data() const { return _string; }
int String::FindFirst(char ch) const
{
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] == ch)
			return i;
	}

	return -1;
}
int String::FindFirst(const String& s) const
{
	if (s._size > _size) return -1;
	if (s._size == 0) return 0;

	for (int i = 0; i <= _size - s._size; i++)
	{
		if (IsStringFound(i, s))
			return i;
	}

	return -1;
}
int String::FindLast(char ch) const
{
	for (int i = _size - 1; i >= 0; i--)
	{
		if (_string[i] == ch)
			return i;
	}

	return -1;
}
int String::FindLast(const String& s) const
{
	if (s._size > _size) return -1;
	if (s._size == 0) return 0;

	for (int i = _size - s._size; i >= 0; i--)
	{
		if (IsStringFound(i, s))
			return i;
	}

	return -1;
}
int* String::FindAll(char ch, int& count) const
{
	int occurrences = 0;
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] == ch)
			occurrences++;
	}

	count = occurrences;
	if (count == 0) return nullptr;

	int* result = new int[count];
	int index = 0;
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] == ch)
			result[index++] = i;
	}

	return result;
}
int* String::FindAll(const String& s, int& count) const
{
	if (s._size == 0 || s._size > _size)
	{
		count = 0;
		return nullptr;
	}

	int occurrences = 0;
	for (int i = 0; i <= _size - s._size; i++)
	{
		if (IsStringFound(i, s)) occurrences++;
	}

	count = occurrences;
	if (count == 0) return nullptr;

	int* result = new int[count];
	int index = 0;
	for (int i = 0; i <= _size - s._size; i++)
	{
		if (IsStringFound(i, s)) result[index++] = i;
	}

	return result;
}

void String::RemoveAt(int index)
{
	if (index < 0 || index >= _size)
		throw "`Index out of bounds.";

	for (int i = index; i < _size - 1; i++)
		_string[i] = _string[i + 1];

	_size--;
	_string[_size] = '\0';
}
void String::InsertAt(int index, char c)
{
	if (index < 0 || index > _size)
		throw "Index out of bounds.";

	char* newString = new char[_size + 2];
	for (int i = 0; i < index; i++)
		newString[i] = _string[i];

	newString[index] = c;

	for (int i = index; i < _size; i++)
		newString[i + 1] = _string[i];
	newString[_size + 1] = '\0';

	delete[] _string;
	_string = newString;
	_size++;
}
void String::InsertAt(int index, const String& s)
{
	if (index < 0 || index >= _size)
		throw "`Index out of bounds.";

	char* newString = new char[_size + s._size + 1];
	for (int i = 0; i < index; i++)
		newString[i] = _string[i];

	for (int i = 0; i < s._size; i++)
		newString[index + i] = s._string[i];

	for (int i = index; i < _size; i++)
		newString[index + s._size + i - index] = _string[i];
	newString[_size + s._size] = '\0';

	delete[] _string;
	_string = newString;
	_size += s._size;
}

void String::RemoveFirst(char ch)
{
	int index = FindFirst(ch);

	if (index != -1)
		RemoveAt(index);
}
void String::RemoveLast(char ch)
{
	int index = FindLast(ch);

	if (index != -1)
		RemoveAt(index);
}
void String::RemoveAll(char ch)
{
	int write = 0;
	for (int read = 0; read < _size; read++)
	{
		if (_string[read] != ch)
			_string[write++] = _string[read];
	}

	_size = write;
	_string[_size] = '\0';
}

void String::Clear()
{
	delete[] _string;

	_size = 0;
	_string = new char[1];
	_string[0] = '\0';
}

String& String::ToUpper()
{
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] >= 'a' && _string[i] <= 'z')
			_string[i] = (_string[i] - 'a') + 'A';
	}

	return *this;
}
String& String::ToLower()
{
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] >= 'A' && _string[i] <= 'Z')
			_string[i] = (_string[i] - 'A') + 'a';
	}

	return *this;
}
String& String::Reverse()
{
	for (int i = 0; i < _size / 2; i++)
	{
		char t = _string[i];
		_string[i] = _string[_size - 1 - i];
		_string[_size - 1 - i] = t;
	}

	return *this;
}

String String::SubString(int start, int length) const
{
	if (start < 0 || start >= _size)
		throw "Start index out of bounds.";
	else if (length < 0)
		throw "Length cannot be negative.";

	if (length == 0)
		return String();

	if (start + length > _size)
		length = _size - start;

	char* temp = new char[length + 1];
	for (int i = 0; i < length; i++)
		temp[i] = _string[start + i];
	temp[length] = '\0';

	String result(temp);
	delete[] temp;
	return result;
}
bool String::StartsWith(const String& s) const
{
	if (s._size > _size) return false;
	return IsStringFound(0, s);
}
bool String::EndsWith(const String& s) const
{
	if (s._size > _size) return false;
	return IsStringFound(_size - s._size, s);
}
bool String::Contains(const String& s) const
{
	return FindFirst(s) != -1;
}
bool String::Contains(char ch) const
{
	return FindFirst(ch) != -1;
}

void String::ReplaceFirst(char from, char to)
{
	int index = FindFirst(from);
	if (index != -1)
		_string[index] = to;
}
void String::ReplaceLast(char from, char to)
{
	int index = FindLast(from);
	if (index != -1)
		_string[index] = to;
}
void String::ReplaceAll(char from, char to)
{
	for (int i = 0; i < _size; i++)
	{
		if (_string[i] == from)
			_string[i] = to;
	}
}
void String::ReplaceFirst(const String& from, const String& to)
{
	int index = FindFirst(from);
	if (index == -1) return;

	int newSize = _size - from._size + to._size;
	char* newString = new char[newSize + 1];

	for (int i = 0; i < index; i++)
		newString[i] = _string[i];

	for (int i = 0; i < to._size; i++)
		newString[index + i] = to._string[i];

	for (int i = index + from._size; i < _size; i++)
		newString[to._size + i - from._size] = _string[i];
	newString[newSize] = '\0';

	delete[] _string;
	_string = newString;
	_size = newSize;
}
void String::ReplaceLast(const String& from, const String& to)
{
	int index = FindLast(from);
	if (index == -1) return;

	int newSize = _size - from._size + to._size;
	char* newString = new char[newSize + 1];

	for (int i = 0; i < index; i++)
		newString[i] = _string[i];

	for (int i = 0; i < to._size; i++)
		newString[index + i] = to._string[i];

	for (int i = index + from._size; i < _size; i++)
		newString[to._size + i - from._size] = _string[i];
	newString[newSize] = '\0';

	delete[] _string;
	_string = newString;
	_size = newSize;
}
void String::ReplaceAll(const String& from, const String& to)
{
	if (from._size == 0) return;

	int count;
	int* indices = FindAll(from, count);
	if (count == 0) return;

	int newSize = _size + count * (to._size - from._size);
	char* newString = new char[newSize + 1];

	int readPos = 0;
	int writePos = 0;
	int matchIndex = 0;

	while (readPos < _size)
	{
		if (matchIndex < count && readPos == indices[matchIndex])
		{
			for (int i = 0; i < to._size; i++)
				newString[writePos++] = to._string[i];

			readPos += from._size;
			matchIndex++;
		}
		else
		{
			newString[writePos++] = _string[readPos++];
		}
	}
	newString[writePos] = '\0';

	delete[] indices;
	delete[] _string;
	_string = newString;
	_size = newSize;
}

String& String::PadLeft(int totalWidth, char padChar)
{
	if (totalWidth <= _size) return *this;

	int padCount = totalWidth - _size;
	char* newString = new char[totalWidth + 1];

	for (int i = 0; i < padCount; i++)
		newString[i] = padChar;

	for (int i = 0; i < _size; i++)
		newString[padCount + i] = _string[i];
	newString[totalWidth] = '\0';

	delete[] _string;
	_string = newString;
	_size = totalWidth;

	return *this;
}
String& String::PadRight(int totalWidth, char padChar)
{
	if (totalWidth <= _size) return *this;

	int padCount = totalWidth - _size;
	char* newString = new char[totalWidth + 1];

	for (int i = 0; i < _size; i++)
		newString[i] = _string[i];

	for (int i = 0; i < padCount; i++)
		newString[_size + i] = padChar;
	newString[totalWidth] = '\0';

	delete[] _string;
	_string = newString;
	_size = totalWidth;

	return *this;
}

bool String::IsEmpty() const { return _size == 0; }
bool String::IsAlpha() const
{
	if (_size == 0) return false;

	for (int i = 0; i < _size; i++)
	{
		if (!((_string[i] >= 'a' && _string[i] <= 'z') || (_string[i] >= 'A' && _string[i] <= 'Z')))
			return false;
	}

	return true;
}
bool String::IsNumeric() const
{
	if (_size == 0) return false;

	int start = (_string[0] == '-') ? 1 : 0;
	if (start == _size) return false;

	for (int i = start; i < _size; i++)
	{
		if (!(_string[i] >= '0' && _string[i] <= '9'))
			return false;
	}

	return true;
}
bool String::IsAlphaNumeric() const
{
	if (_size == 0) return false;

	for (int i = 0; i < _size; i++)
	{
		bool isAlpha = (_string[i] >= 'a' && _string[i] <= 'z') || (_string[i] >= 'A' && _string[i] <= 'Z');
		bool isDigit = (_string[i] >= '0' && _string[i] <= '9');

		if (!isAlpha && !isDigit)
			return false;
	}

	return true;
}

int String::StringToInteger(const String s) { return s.StringToInteger(); }
String String::IntegerToString(int num)
{
	if (num == 0) return String('0');

	bool negative = (num < 0);
	if (negative) num = -num;

	char intChar[12];
	int size = 0;
	while (num > 0)
	{
		intChar[size++] = (num % 10) + '0';
		num /= 10;
	}

	if (negative) intChar[size++] = '-';
	intChar[size] = '\0';

	for (int j = 0; j < size / 2; j++)
	{
		char t = intChar[j];
		intChar[j] = intChar[size - j - 1];
		intChar[size - j - 1] = t;
	}

	return String(intChar);
}
String String::Trim(const String& s) { return String(s).Trim(); }
String String::ToUpper(String& s) { return String(s).ToUpper(); }
String String::ToLower(String& s) { return String(s).ToLower(); }
String String::Reverse(String& s) { return String(s).Reverse(); }

String& String::operator= (const String& other)
{
	if (this != &other)
	{
		delete[] _string;
		_size = other._size;
		_string = new char[_size + 1];

		CopyString(_string, other._string);
	}

	return *this;
}
bool String::operator== (const String& other) const
{
	if (this == &other) return true;
	return IsEqual(other);
}
bool String::operator!= (const String& other) const { return !IsEqual(other); }
bool String::operator<  (const String& other) const { return IsLess(other); }
bool String::operator>  (const String& other) const { return IsGreater(other); }
bool String::operator<= (const String& other) const { return !IsGreater(other); }
bool String::operator>= (const String& other) const { return !IsLess(other); }
String String::operator+ (const String& other) const { return Concat(other); }
String& String::operator+= (const String& other) { return Append(other); }
char String::operator[] (int i) const
{
	if (i < 0 || i >= _size) throw "Index out of bounds";
	return _string[i];
}

char& String::operator[] (int i)
{
	if (i < 0 || i >= _size) throw "Index out of bounds.";
	return _string[i];
}

std::ostream& operator<< (std::ostream& os, const String& s)
{
	os << s._string;
	return os;
}
std::istream& operator>> (std::istream& is, String& s)
{
	char temp[1000];
	is >> temp;
	s = String(temp);

	return is;
}
