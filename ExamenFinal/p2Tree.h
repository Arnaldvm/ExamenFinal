// ----------------------------------------------------
// Generic tree implementation, any number of childs --
// ----------------------------------------------------

#ifndef __P2TREE_H__
#define __P2TREE_H__

#include "p2List.h"
#include "p2Stack.h"

// Tree node -------------------------------------------------------
template<class tdata>
class p2TreeNode
{

public:

	tdata				data;
	p2TreeNode*			parent;
	p2List<p2TreeNode*> childs;

public:

	p2TreeNode(const tdata& _data)
	{
		data = _data;
		parent = NULL;
	}

	void AddChild(p2TreeNode* node)
	{
		assert(node);

		childs.add(node);
		node->parent = this;
	}

	bool RemoveChild(p2TreeNode* node)
	{
		assert(node);
		bool ret = false;

		p2List_item<p2TreeNode*>* item = childs.start;
		for (; item != NULL; item = item->next)
		{
			p2TreeNode* child = item->data;

			if (node == child)
			{
				childs.del(item);
				node->parent = NULL;
				ret = true;
				break;
			}
		}

		return ret;
	}

	void PreOrderRecursive(p2List<p2TreeNode<tdata>*>* list)
	{
		list->add(this);

		p2List_item<p2TreeNode*>* item = childs.start;

		for (; item != NULL; item = item->next)
			item->data->PreOrderRecursive(list);
	}

	void InOrderRecursive(p2List<p2TreeNode<tdata>*>* list)
	{
		p2List_item<p2TreeNode*>* item = childs.start;
		unsigned int mid = childs.count() / 2;

		for (unsigned int i = 0; i < mid; ++i, item = item->next)
			item->data->InOrderRecursive(list);

		list->add(this);

		for (; item != NULL; item = item->next)
			item->data->InOrderRecursive(list);
	}

	void PostOrderRecursive(p2List<p2TreeNode<tdata>*>* list)
	{
		p2List_item<p2TreeNode*>* item = childs.start;

		for (; item != NULL; item = item->next)
			item->data->PostOrderRecursive(list);

		list->add(this);
	}


	p2TreeNode<tdata>* FindRecursive(const tdata& node)
	{
		if (node == data)
			return this;

		p2TreeNode<tdata>* result = NULL;
		p2List_item<p2TreeNode*>* item = childs.start;
		for (; item != NULL; item = item->next)
		{
			p2TreeNode* child = item->data;
			result = child->FindRecursive(node);

			if (result != NULL)
				break;
		}

		return result;
	}

	void GatherAll(p2List<p2TreeNode*>* list)
	{
		assert(list);
		list->add(this);

		p2List_item<p2TreeNode*>* item = childs.start;

		for (; item != NULL; item = item->next)
		{
			p2TreeNode* child = item->data;
			child->GatherAll(list);
		}
	}


};

// Tree class -------------------------------------------------------
template<class tdata>
class p2Tree
{
public:

	// Constructor
	p2Tree(const tdata& _data) : trunk(_data)
	{}

	// Destructor
	virtual ~p2Tree()
	{}

	void PreOrderRecursive(p2List<p2TreeNode<tdata>*>* list)
	{
		trunk.PreOrderRecursive(list);
	}

	void PostOrderRecursive(p2List<p2TreeNode<tdata>*>* list)
	{
		trunk.PostOrderRecursive(list);
	}

	void InOrderRecursive(p2List<p2TreeNode<tdata>*>* list)
	{
		trunk.InOrderRecursive(list);
	}

	void PreOrderIterative(p2List<p2TreeNode<tdata>*>* list)
	{
		Stack<p2TreeNode<tdata>*> stack;
		p2TreeNode<tdata>* node = &trunk;

		while (node != NULL || stack.pop(node))
		{
			list->add(node);

			p2List_item<p2TreeNode<tdata>*>* item = node->childs.end;
			for (; item != node->childs.start; item = item->prev)
				stack.pushBack(item->data);

			node = (item != NULL) ? item->data : NULL;
		}
	}

	void PostOrderIterative(p2List<p2TreeNode<tdata>*>* list)
	{
		Stack<p2TreeNode<tdata>*> stack;
		p2TreeNode<tdata>* node = &trunk;

		while (node != NULL || stack.pop(node))
		{
			p2List_item<p2TreeNode<tdata>*>* item = node->childs.end;

			if (item != NULL && list->find(item->data) == -1)
			{
				stack.pushBack(node);
				for (; item != node->childs.start; item = item->prev)
					stack.pushBack(item->data);

				node = item->data;
			}
			else
			{
				list->add(node);
				node = NULL;
			}
		}
	}

	void InOrderIterative(p2List<p2TreeNode<tdata>*>* list)
	{
		Stack<p2TreeNode<tdata>*> stack;
		p2TreeNode<tdata>* node = NULL;
		p2DynArray<p2TreeNode<tdata>*> childs;

		childs.PushBack(&trunk);

		while (childs.Count() > 0 || stack.pop(node))
		{
			if (childs.Count() > 0)
			{
				for (int i = childs.Count() - 1; i >= 0; --i)
					stack.pushBack(childs[i]);

				node = childs[0];
				childs.Clear();

				// Add all the childs on the right
				if (node != NULL)
				{
					p2List_item<p2TreeNode<tdata>*>* item = node->childs.start;
					p2List_item<p2TreeNode<tdata>*>* end = node->childs.At(node->childs.count() / 2);

					while (item != end)
					{
						childs.PushBack(item->data);
						item = item->next;
					}
				}
			}
			else
			{
				list->add(node);

				// Add all childs on the right
				p2List_item<p2TreeNode<tdata>*>* item = node->childs.At(node->childs.count() / 2);

				while (item != NULL)
				{
					childs.PushBack(item->data);
					item = item->next;
				}
			}
		}
	}


	void Add(const tdata& data, const tdata& parent)
	{
		p2TreeNode<tdata>* p = trunk.FindRecursive(parent);
		p2TreeNode<tdata>* node = new p2TreeNode<tdata>(data);
		p->AddChild(node);
	}

	void Add(const tdata& data)
	{
		p2TreeNode<tdata>* node = new p2TreeNode<tdata>(data);
		trunk.AddChild(node);
	}

	bool DelRecursive(const tdata& data)
	{
		bool ret = false;

		p2TreeNode<tdata>* node = trunk.FindRecursive(data);

		if (node != NULL)
		{
			p2List<p2TreeNode<tdata>*> results;
			node->GatherAll(&results);

			p2List_item<p2TreeNode<tdata>*>* item = results.start;

			for (; item != NULL; item = item->next)
			{
				p2TreeNode<tdata>* child = item->data;

				if (child->parent)
					child->parent->RemoveChild(child);
			}

			ret = true;
		}

		return ret;
	}



public:

	p2TreeNode<tdata>	trunk;

};

#endif // __P2TREE_H__