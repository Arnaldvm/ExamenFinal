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

	unsigned int Find(const char* string) const
	{
		unsigned int ret = 0;

		if (string != NULL)
		{
			unsigned int len = strlen(string);

			for (unsigned int i = 0; i < size - len; ++i)
			{
				if (strncmp(string, &str[i], len) == 0)
				{
					i += len;
					++ret;
				}
			}
		}

		return ret;
	}

	
	unsigned int Substitute(const char* src, const char *dst)
	{
		assert(src);
		assert(dst);

		unsigned int instances = Find(src);

		if (instances > 0)
		{
			unsigned int src_len = strlen(src);
			unsigned int dst_len = strlen(dst);
			unsigned int diff = dst_len - src_len;
			unsigned int needed_size = 1 + strlen(str) + (diff * instances);

			if (size < needed_size)
			{
				char* tmp = str;
				Alloc(needed_size);
				strcpy_s(str, size, tmp);
				delete tmp;
			}

			for (unsigned int i = 0; i < size - src_len; ++i)
			{
				if (strncmp(src, &str[i], src_len) == 0)
				{
					// make room
					for (unsigned int j = strlen(str) + diff; j > i + diff; --j)
					{
						str[j] = str[j - diff];
					}

					// copy
					for (unsigned int j = 0; j < dst_len; ++j)
					{
						str[i++] = dst[j];
					}
				}
			}

		}

		return instances;
	}

	
	void trim()
	{
		int emptyBegining = 0;
		
		for (int i = size; str[i] == ' '; i--)
			str[i] = '\0';

		for (int j = 0; str[j] == ' '; j++)
			emptyBegining++;
	}

	void opTrim()
	{
		
		char* end = str + size;
		while (*--end == ' ') *end = '\0';

		char* start = str;
		while (*++start == ' ');

		for (int i = 0; i < Length() + 1; i++)
			str[i] = start[i];
	}


	//-----------EXAMEN FINAL------------------------

	void Cut(const unsigned int first, const unsigned int last){

		assert(first < size, last < size);
		
		unsigned int gap = last - first;
		if (last != 0) {
			for (unsigned int i = 0; i <= gap; i++) {
				str[first + i] = str[last + i + 1];
				size--;
			
			}
		}
		if (last == 0){
			for (unsigned int i = size; i > first + 1; i--) {
				size--;
			}
		}

		str[size - 1] = '\0';
		
		

	}



private:

	void Alloc(unsigned int requiered_memory)
	{
		size = requiered_memory;
		str = new char[size];
	}

};

#endif // __p2SString_H__