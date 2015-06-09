#ifndef __p2SString_H__
#define __p2SString_H__

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>



class p2SString
{
private:

	char* str;
	unsigned int size;

public:

	// Constructors
	p2SString()
	{
		Alloc(1);
		Clear();
	}

	p2SString(unsigned int size)
	{
		if (size == 0)
			Alloc(1);
		else
			Alloc(size);
		Clear();
	}

	p2SString(const p2SString& string)
	{
		Alloc(string.size);
		strcpy_s(str, size, string.str);
	}

	p2SString(const char *format, ...)
	{
		size = 0;

		if (format != NULL)
		{
			static char tmp[4096];
			static va_list  ap;

			// Construct the string from variable arguments
			va_start(ap, format);
			int res = vsprintf_s(tmp, 4096, format, ap);
			va_end(ap);

			if (res > 0)
			{
				Alloc(res + 1);
				strcpy_s(str, size, tmp);
			}
		}

		if (size == 0)
		{
			Alloc(1);
			Clear();
		}

	}

	// Destructor
	virtual ~p2SString()
	{
		if (str != NULL)
			delete[] str;
	}

	// Operators
	bool operator== (const p2SString& string) const
	{
		if (strcmp(string.str, str) == 0)
			return true;
		else
			return false;
	}

	bool operator== (const char* string) const
	{
		if (string != NULL){
			if (strcmp(string, str) == 0)
				return true;
		}
		return false;
	}

	bool operator!= (const p2SString& string) const
	{
		if (strcmp(string.str, str) == 1)
			return true;
		else
			return false;
	}

	bool operator!= (const char* string) const
	{
		if (string != NULL){
			if (strcmp(string, str) == 1)
				return true;
		}
			return false;
	}

	const p2SString& operator= (const p2SString& string)
	{
		if (string.size + 1 > size) {
			delete[] str;
			Alloc(string.size + 1);
		}
		else
			Clear(); 

		strcpy_s(str, size, string.str);
		return(*this);

	}

	const p2SString& operator= (const char* string)
	{
		if (string != NULL) {
			if (strlen(string) + 1 > size){
				delete[] str;
				Alloc(strlen(string) + 1);
			}
			else
				Clear();

			strcpy_s(str, size, string);
		}
		return (*this);
	}


	const p2SString& operator+= (const p2SString& string)
	{
		unsigned int need_size = string.Length() + Length() + 1;

		if (need_size > size)
		{
			char* tmp = str;
			Alloc(need_size);
			strcpy_s(str, size, tmp);
			delete[] tmp;
		}

		strcat_s(str, size, string.str);

		return(*this);
	}

	const p2SString& operator+= (const char* string)
	{
		if (string != NULL)
		{
			unsigned int need_size = strlen(string) + Length() + 1;

			if (need_size > size)
			{
				char* tmp = str;
				Alloc(need_size);
				strcpy_s(str, size, tmp);
				delete[] tmp;
			}

			strcat_s(str, size, string);
		}

		return(*this);
	}

	// Utils
	unsigned int Length() const
	{
		return strlen(str);
	}

	void Clear()
	{
		str[0] = '\0';
	}

	const char* GetString() const
	{
		return str;
	}

	unsigned int GetCapacity() const
	{
		return size;
	}

	const p2SString& prefix(const p2SString& string)
	{
		assert(Length() + string.Length() < 4096);

		char tmp[4096];
		strcpy_s(tmp, 4096, string.str);
		strcat_s(tmp, 4096, str);
		unsigned int need_size = strlen(tmp) + 1;
		if (need_size > size)
		{
			delete[] str;
			Alloc(need_size);
		}
		strcpy_s(str, size, tmp);
		return(*this);
	}

	int countStrings(const char* a)const
	{
		unsigned int counter = 0;

		if (a != NULL)
		{
			unsigned int len = strlen(a);
			for (unsigned int i = 0; i < size - len; i++)
			{
				if (strncmp(a, &str[i], len) == 0)
				{
					i += len;
					++counter;
				}
			}
		}
		return counter;
	}

	//Clean

	void trim()
	{
		int emptyBegining = 0;
		//final
		for (int i = size; str[i] == ' '; i--)
			str[i] = '\0';

		//principi
		for (int j = 0; str[j] == ' '; j++)
			emptyBegining++;
	}

	void opTrim()
	{
		//right
		char* end = str + size;
		while (*--end == ' ') *end = '\0';

		//Left
		char* start = str;
		while (*++start == ' ');

		for (int i = 0; i < Length() + 1; i++)
			str[i] = start[i];
	}


private:

	void Alloc(unsigned int requiered_memory)
	{
		size = requiered_memory;
		str = new char[size];
	}

};

#endif // __p2SString_H__