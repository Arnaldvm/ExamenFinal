// ----------------------------------------------------
// FIFO implementation with single linked list  -------
// ----------------------------------------------------

#ifndef _p2Queue_H_
#define _p2Queue_H_

#include <stdio.h>

template<class TYPE>
struct qNode
{
	TYPE value;
	qNode<TYPE>* next;
	qNode<TYPE>* previous;

	inline qNode(const TYPE& _value)
	{
		value = _value;
		next = NULL;
	}

	~qNode(){}
};

template<class TYPE>
class p2Queue
{
public:

	qNode<TYPE>* start;
	qNode<TYPE>* end;

private:

	unsigned int size;

public:

	//Constructor
	inline p2Queue()
	{
		start = end = NULL;
		size = 0;
	}

	//Destructor
	~p2Queue()
	{
		delAll();
	}

	//Get Size
	unsigned int count()
	{
		return size;
	}

	//push
	void push(const TYPE& value)
	{
		qNode<TYPE>* newqNode = new qNode<TYPE>(value);
		//newqNode->value = value;

		if (start == NULL)
		{
			start = end = newqNode;
		}
		else
		{
			newqNode->previous = end;
			end->next = newqNode;
			end = newqNode;
		}
		size++;
	}

	//pop
	bool pop(TYPE& value)
	{
		if (start == NULL || end == NULL)
		{
			return false;
		}
		else
		{
			qNode<TYPE>* tmp = start;
			start = start->next;
			start->previous = NULL;
			value = tmp->value;
			delete tmp;
			--size;
		}
		return(true);
	}

	const TYPE* peek(unsigned int index)
	{
		unsigned int i = 0;
		qNode<TYPE>* tmp;

		for (tmp = start; tmp != NULL && i < index; tmp = tmp->next)
		{
			++i;
		}

		if (tmp != NULL)
			return &(tmp->Value);

		return NULL;
	}

	bool del(unsigned int x)
	{
		if (start == NULL || end == NULL)
		{
			return false;
		}
		else
		{
			if (x == 0)
			{
				start = start->next;
				return(true);
			}

			qNode* tmp = start;
			qNode* tmp2;

			for (unsigned int i = 1; i < x; i++)
			{
				if (tmp == NULL)
				{
					return(false);
				}
				tmp = tmp->next;
			}
			tmp2 = tmp->next;
			if (tmp2->next != NULL)
			{
				tmp->next = tmp2->next;
				tmp = tmp2->next;
				tmp->previous = tmp2->previous;
			}
			else
			{
				end = end->previous;
				end->next = NULL;
			}
		}
		delete tmp2;
		--size;
		return(true)
	}


	//Destroy and free all mem
	void delAll()
	{
		if (start != NULL)
		{
			qNode<TYPE>* tmp;
			while (start != NULL)
			{
				tmp = start;
				start = start->next;
				delete tmp;
			}
			start = end = NULL;
			size = 0;
		}
	}

};



#endif