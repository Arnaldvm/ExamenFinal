#ifndef __p2List_H__
#define __p2List_H__

#include <conio.h>
#include <iostream>
#include <Assert.h>

/**
* Contains items from double linked list
*/
template<class tdata>
struct p2List_item
{
	tdata                 data;
	p2List_item<tdata>*   next;
	p2List_item<tdata>*   prev;

	inline p2List_item(const tdata& _data)
	{
		data = _data;
		next = prev = NULL;
	}

	~p2List_item()
	{}
};

/**
* Manages a double linked list
*/
template<class tdata>
class p2List
{

public:

	p2List_item<tdata>*   start;
	p2List_item<tdata>*   end;

private:

	unsigned int  size;

public:

	/**
	* Constructor
	*/
	inline p2List()
	{
		start = end = NULL;
		size = 0;
	}

	/**
	* Destructor
	*/
	~p2List()
	{
		clear();
	}

	/**
	* Get Size
	*/
	unsigned int count() const
	{
		return size;
	}

	/**
	* Add new item
	*/
	unsigned int add(const tdata& item)
	{
		p2List_item<tdata>*   p_data_item;
		p_data_item = new p2List_item < tdata >(item);

		if (start == NULL)
			start = end = p_data_item;
		else {

			p_data_item->prev = end;
			end->next = p_data_item;
			end = p_data_item;
		}

		return(++size);
	}

	/**
	* Deletes an item from the list
	*/
	bool del(p2List_item<tdata>* item)
	{
		if(item == NULL)
		{
			return (false);
		}

		// Now reconstruct the list
		if(item->prev != NULL)
		{
			item->prev->next = item->next;

			if(item->next != NULL)
				item->next->prev = item->prev;
			else
				end = item->prev;
			
		}
		else
		{
			if(item->next)
			{
				item->next->prev = NULL;
				start = item->next;
			}
			else
				start = end = NULL;
		}

		delete item;
		--size;
		return(true);
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		p2List_item<tdata>*   p_data;
		p2List_item<tdata>*   p_next;
		p_data = start;

		while (p_data != NULL)
		{
			p_next = p_data->next;
			delete p_data;
			p_data = p_next;
		}

		start = end = NULL;
		size = 0;
	}

	/**
	* read / write operator access directly to a position in the list
	*/
	tdata& operator  [](const unsigned int index)
	{
		p2List_item<tdata>* tmp = start;
		assert(size > index);

		for (unsigned int i = index; i > 0; i--)
			tmp = tmp->next;
		return tmp->data;
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const tdata& operator  [](const unsigned int index) const
	{
		p2List_item<tdata>* tmp = start;
		assert(size > index);

		for (unsigned int i = index; i > 0; i--)
			tmp = tmp->next;
		return tmp->data;
	}

	/**
	* const read operator access directly to a position in the list
	*/
	const p2List<tdata>& operator +=(const p2List<tdata>& other_list)
	{
		p2List_item<tdata>*   p_item = other_list.start;

		while (p_item != NULL)
		{
			add(p_item->data);
			p_item = p_item->next;
		}

		return(*this);
	}

	/**
	* const access to a node in a position in the list
	*/
	const p2List_item<tdata>* At(unsigned int index) const
	{
		long                  pos = 0;
		p2List_item<tdata>*   p_item = start;

		while (p_item != NULL)
		{
			if (pos++ == index)
				break;

			p_item = p_item->next;
		}

		return p_item;
	}

	/**
	* access to a node in a position in the list
	*/
	p2List_item<tdata>* At(unsigned int index)
	{
		long                  pos = 0;
		p2List_item<tdata>*   p_item = start;

		while (p_item != NULL)
		{
			if (pos++ == index)
				break;

			p_item = p_item->next;
		}

		return p_item;
	}

	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while (swapped)
		{
			swapped = false;
			p2List_item<tdata>* tmp = start;

			while (tmp != NULL && tmp->next != NULL)
			{
				++ret;
				if (tmp->data > tmp->next->data)
				{
					SWAP(tmp->data, tmp->next->data);
					swapped = true;
				}

				tmp = tmp->next;
			}
		}

		return ret;
	}

	unsigned int delNodes(unsigned int position, unsigned int number){

		if (position > size || number == 0)
			return (0);

		unsigned int result = 1;
		
		p2List_item<tdata>* tmp = start;
		for (unsigned int i = 0; i < position; i++)
			tmp = tmp->next;

		p2List_item<tdata>* tmp2 = tmp;
		for (unsigned int i = 1; i < number && tmp2->next != NULL; i++)
			tmp2 = tmp2->next;

		if (tmp->prev != NULL)
		{
			tmp->prev->next = tmp2->next;
			
			
			if (tmp2->next != NULL)
				tmp2->next->prev = tmp->prev;
			else
				end = tmp->prev;

		}
		else
		{
			if (tmp2->next)
			{
				tmp2->next->prev = NULL;
				start = tmp2->next;
			}
			else
				start = end = NULL;
		}

		p2List_item<tdata>* tmp3 = tmp;
		while (tmp3 != tmp2){

			tmp3 = tmp3->next;
			delete tmp;
			tmp = tmp3;
			result++;
		}

		delete tmp2;
		size -= result;
		return result;

	}

	/* returns the first apperance of data as index (-1 if not found)
	*/
	int find(const tdata& data)
	{
		p2List_item<tdata>* tmp = start;
		int index = 0;

		while (tmp != NULL)
		{
			if (tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}

	bool InsertAfter(unsigned int position, const p2List<tdata>& list){

		if (position > size)
			return false;
		if (start == NULL){
			start = list.start;
			end = list.end;
			size = list.size;
			return true;
		}
		p2List_item<tdata>* tmp = start;
		for (unsigned int i = 0; i < position; i++)
			tmp = tmp->next;
		p2List_item<tdata>* tmp2 = list.start;
		p2List_item<tdata>* tmp3 = tmp->next;
		
		tmp->next = tmp2;
		tmp2->prev = tmp;
		tmp3->prev = list.end;
		list.end->next = tmp3;
		size += list.count();
		return true;
		
			
	}
	/*bool Insert(const p2DynArray<VALUE>& array, unsigned int position)
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
	}*/

};
#endif /*__p2List_H__*/