// ----------------------------------------------------
// Array that resizes dynamically   -------------------
// ----------------------------------------------------

#ifndef __P2DYNARRAY_H__
#define __P2DYNARRAY_H__

#include <conio.h>
#include <iostream>
#include <Assert.h>
#include "Swap.h"


template<class VALUE>
class p2DynArray
{
private:

	VALUE*			data;
	unsigned int	mem_capacity;
	unsigned int	num_elements;

public:

	// Constructors
	p2DynArray() 
	{
		data = NULL;
		mem_capacity = 0;
		num_elements = 0;
	}

	p2DynArray(unsigned int capacity) 
	{
		data = NULL;
		mem_capacity = 0;
		num_elements = 0;
		Alloc(capacity);
	}

	// Destructor
	~p2DynArray()
	{ 
		delete[] data;
	}

	// Operators
	VALUE& operator[](unsigned int index)
	{
		assert(index < num_elements);
		return data[index];
	}

	const VALUE& operator[](unsigned int index) const
	{
		assert(index < num_elements);
		return data[index];
	}

	// Data Management
	void PushBack(const VALUE& element)
	{
		if (num_elements >= mem_capacity)
		{
			Alloc(mem_capacity+1);
		}

		data[num_elements++] = element;
	}

	bool Pop(VALUE& result)
	{
		if (num_elements != NULL){
			result = data[--num_elements];
			return true;
		}

		return false;
	}

	void Clear()
	{
		num_elements = 0;
	}

	bool Insert(const VALUE& element, unsigned int position)
	{
		if (position > num_elements)
			return false;
		if (position == num_elements)
		{
			PushBack(element);
			return true;
		}
		else {
			if (num_elements >= mem_capacity)
				Alloc(mem_capacity + 1);
			for (unsigned int i = num_elements; i > position; i--)
				data[i] = data[i--];
			data[position] = element;
			num_elements++;
			return true;

		}
	}



	VALUE* At(unsigned int index)
	{
		VALUE* result = NULL;

		if (index < num_elements)
			return result = &data[index];

		return result;
	}

	const VALUE* At(unsigned int index) const
	{
		VALUE* result = NULL;

		if (index < num_elements)
			return result = &data[index];

		return result;
	}

	// Sort
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while (swapped)
		{
			swapped = false;
			for (unsigned int i = 0; i < num_elements - 2; ++i)
			{
				++ret;
				if (data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					swapped = true;
				}
			}
		}

		return ret;
	}


	int BubbleSortOptimized()
	{
		int ret = 0;
		unsigned int count;
		unsigned int last = num_elements - 2;

		while (last > 0)
		{
			count = last;
			last = 0;
			for (unsigned int i = 0; i < count; ++i)
			{
				++ret;
				if (data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					last = i;
				}
			}
		}
		return ret;
	}


	int CombSort()
	{
		int ret = 0;
		bool swapped = true;
		int gap = num_elements - 1;
		float shrink = 1.3f;

		while (swapped || gap > 1)
		{
			gap = MAX(1, gap / shrink);

			swapped = false;
			for (unsigned int i = 0; i + gap < num_elements - 1; ++i)
			{
				++ret;
				if (data[i] > data[i + gap])
				{
					SWAP(data[i], data[i + gap]);
					swapped = true;
				}
			}
		}

		return ret;
	}

	bool Insert(const p2DynArray<VALUE>& array, unsigned int position)
	{
		if (position > num_elements)
			return false;

		if (num_elements + array.num_elements > mem_capacity)
			Alloc(num_elements + array.num_elements + 1);

		for (unsigned int i = position; i < position + array.num_elements; ++i)
		{
			data[i + array.num_elements] = data[i];
			data[i] = array[i - position];
			++num_elements;
		}

		return true;
	}

	// Utils
	unsigned int GetCapacity() const
	{
		return mem_capacity;
	}

	unsigned int Count() const
	{
		return num_elements;
	}

	unsigned int removeWastedMemory() {

		unsigned int removed = mem_capacity - num_elements;

		if (num_elements < mem_capacity)
			Alloc(num_elements);
		return removed;
	}

	void Flip()
	{
		VALUE* start = &data[0];
		VALUE* end = &data[num_elements - 1];

		while (start < end)
			SWAP(*start++, *end--);
	}

	const p2DynArray<VALUE>& operator += (const p2DynArray<VALUE>& arr)
	{
		if (arr.data != NULL) {
			
	
			for (unsigned int i = 0; i < arr.Count(); i++) {
				PushBack(arr[i]);
			}

		}
	
		return(*this);
	}

private:

	// Private Utils
	void Alloc(unsigned int mem)
	{
		VALUE* tmp = data;

		mem_capacity = mem;
		data = new VALUE[mem_capacity];

		if (num_elements > mem_capacity)
			mem_capacity = num_elements;

		if (tmp != NULL){

			for (unsigned int i = 0; i < num_elements; i++)
				data[i] = tmp[i];
			delete[] tmp;
		}

	}
};

#endif // __P2DYNARRAY_H__