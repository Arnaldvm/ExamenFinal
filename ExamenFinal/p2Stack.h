#ifndef _Stack_
#define _Stack_

#include <stdio.h>
#include <assert.h>


template<class TYPE>
class Stack
{
private:
	TYPE* data;
	unsigned int alloc_memory;
	unsigned int elements;

public:
	//Constructors
	Stack() {

		data = NULL;
		alloc_memory = 0;
		elements = 0;
	}

	Stack(unsigned int mem_size) {

		data = NULL:
		elements = 0;
		reallocate(mem_size);
	}

	//Destructor
	~Stack() {

		if (data != NULL)
			delete[] data;
	}

	//Operators
	TYPE& operator[] (unsigned int index) {

		assert(index < elements);
		return data[index];
	}

	const TYPE& operator[] (unsigned int index) const {

		assert(index < elements);
		return data[index];
	}

	//Data Managment
	void pushBack(const TYPE& value) {

		if (elements >= alloc_memory)
		{
			reallocate(alloc_memory + 1);
		}
		data[elements++] = value;
	}

	bool pop(TYPE& value) {

		if (elements > 0)
		{
			value = data[--elements];
			return true;
		}
		return false;
	}

	void clear() {

		elements = 0;
	}

	TYPE* at(unsigned int index) {

		TYPE* result = NULL;
		if (index < elements)
		{
			return result = &data[index];
		}
		return result;
	}

	const TYPE* at(unsigned int index) const {

		TYPE* result = NULL;
		if (index < elements)
		{
			return result = &data[index];
		}
		return result;
	}

	//Optimization
	const unsigned int removeWastedMemory() {

		unsigned int lastAllocatedMemory = allocatedMemory;
		Stack<TYPE> tmp(count());
		reallocate(count());
		return(lastAllocatedMemory - allocatedMemory);
	}

	//Utilities
	unsigned int getCapacity() const {

		return allocatedMemory;
	}

	unsigned int count() const {

		return elements;
	}

private:
	//Private Utilities
	void reallocate(unsigned int new_memory_size) {

		TYPE* tmp = data;
		alloc_memory = new_memory_size;
		data = new TYPE[alloc_memory];
		if (elements > alloc_memory)
			elements = alloc_memory;
		if (tmp != NULL) {

			for (unsigned int i = 0; i < elements; ++i)
				data[i] = tmp[i];
			delete[] tmp;
		}
	}
};

#endif