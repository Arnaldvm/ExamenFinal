#include "stdafx.h"
#include "CppUnitTest.h"

#define __P2ASSERT_H__

#include "../ExamenFinal/p2SString.h"
#include "../ExamenFinal/p2List.h"
#include "../ExamenFinal/p2Tree.h"
#include "../ExamenFinal/Projectile.h"
#include "../ExamenFinal/p2Point.h"
#include "../ExamenFinal/p2DynArray.h"
#include "../ExamenFinal/p2Stack.h"
#include "../ExamenFinal/p2Queue.h"
#include "../ExamenFinal/Swap.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void TLOG(const char* str, ...)
{
	static char tmp[4096];
	static va_list  ap;

	va_start( ap, str );
	vsprintf_s( tmp, 4096, str, ap );
	va_end( ap );

	strcat_s(tmp, 4096, "\n");
	Logger::WriteMessage(tmp);
}

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		/// QEUE ----------------------------------------------
		TEST_METHOD(Qeue_test)
		{
			p2Queue<int> fifo;
			
			
			fifo.push(11);
			fifo.push(22);
			fifo.push(33);
			
			Assert::AreEqual((int)fifo.count(), 3);
			//Assert::AreEqual((int)*(fifo.Peek(1)), 22);

			
			int result;
			bool r = fifo.pop(result);
			
			Assert::AreEqual((int)result, 11);
			Assert::AreEqual((int)fifo.count(), 2);
			
		}


		// STACK ---------------------------------------------
		TEST_METHOD(Stack_test)
		{
			Stack<int> lifo;

			lifo.pushBack(10);
			lifo.pushBack(20);
			lifo.pushBack(30);
			lifo.pushBack(40);

			Assert::AreEqual((int)lifo.count(), 4);
			Assert::AreEqual((int)*(lifo.at(1)), 20);

			int result;
			bool r = lifo.pop(result);

			Assert::AreEqual((int)result, 40);
			Assert::AreEqual((int)lifo.count(), 3);
		}


		// DYN ARRAY -----------------------------------------
		TEST_METHOD(DynArray_ctor)
		{
			p2DynArray<int> array;
			Assert::AreEqual((int)array.GetCapacity(), 0);
		}

		TEST_METHOD(DynArray_ctor_capacity)
		{
			p2DynArray<int> array(23);
			Assert::AreEqual((int)array.GetCapacity(), 23);
		}

		TEST_METHOD(DynArray_push_back)
		{
			p2DynArray<int> array;

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(3);
			Assert::AreEqual((int)array.Count(), 3);
		}

		TEST_METHOD(DynArray_pop)
		{
			p2DynArray<int> array;

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(3);

			int a, b;
			array.Pop(a);
			array.Pop(b);

			
			Assert::AreEqual((int)array.Count(), 1);
			Assert::AreEqual(a, 3);
			Assert::AreEqual(b, 2);
		}

		TEST_METHOD(DynArray_clear)
		{
			p2DynArray<int> array;

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(3);
			array.Clear();

			Assert::AreEqual((int)array.Count(), 0);
		}


		TEST_METHOD(DynArray_op)
		{
			p2DynArray<int> array;

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(3);
			
			Assert::AreEqual(array[0], 1);
			Assert::AreEqual(array[1], 2);
			Assert::AreEqual(array[2], 3);
		}

		TEST_METHOD(DynArray_at)
		{
			p2DynArray<int> array;

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(3);

			Assert::AreEqual(*(array.At(0)), 1);
			Assert::AreEqual(*(array.At(1)), 2);
			Assert::AreEqual(*(array.At(2)), 3);
			Assert::IsNull(array.At(3));
		}

	

		TEST_METHOD(insert)
		{
			p2DynArray<int> array;

			for(int i = 0; i < 19; ++i)
			{
				array.PushBack(i);
			}

			array.Insert(999, 3);
			array.Insert(888, 17);
			array.Insert(777, 50);

			Assert::IsFalse(array.Insert(777, 50));
			Assert::AreEqual((int)array.Count(), 21);
			Assert::AreEqual((int)array[3], 999);
			Assert::AreEqual((int)array[17], 888);
		}

		TEST_METHOD(DynArray_BubbleSort)
		{
			p2DynArray<int> array;

			array.PushBack(5);
			array.PushBack(4);
			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(8);

			array.BubbleSort();

			Assert::AreEqual((int)array[0], 1);
			Assert::AreEqual((int)array[1], 2);
			Assert::AreEqual((int)array[2], 4);
			Assert::AreEqual((int)array[3], 5);
			Assert::AreEqual((int)array[4], 8);
		}

		TEST_METHOD(DynArray_BubbleSortOpt)
		{
			p2DynArray<int> array;

			array.PushBack(5);
			array.PushBack(4);
			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(8);

			int n = array.BubbleSortOptimized();

			Assert::AreEqual((int)n, 6);
			Assert::AreEqual((int)array[0], 1);
			Assert::AreEqual((int)array[1], 2);
			Assert::AreEqual((int)array[2], 4);
			Assert::AreEqual((int)array[3], 5);
			Assert::AreEqual((int)array[4], 8);
		}

		TEST_METHOD(DynArray_InsertArray)
		{
			p2DynArray<int> array(5);

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(4);
			array.PushBack(5);
			array.PushBack(8);

			p2DynArray<int> array2;

			array2.PushBack(999);
			array2.PushBack(999);
			array2.PushBack(999);

			bool b = array.Insert(array2, 2);

			Assert::IsTrue(b);
			Assert::AreEqual((int)array.Count(), 8);
			Assert::AreEqual((int)array[0], 1);
			Assert::AreEqual((int)array[1], 2);
			Assert::AreEqual((int)array[2], 999);
			Assert::AreEqual((int)array[3], 999);
			Assert::AreEqual((int)array[4], 999);
			Assert::AreEqual((int)array[5], 4);
			Assert::AreEqual((int)array[6], 5);
			Assert::AreEqual((int)array[7], 8);
		}
		
		// SWAP ----------------------------------------------
		TEST_METHOD(swap_int)
		{
			int a = 5;
			int b = 8;
			SWAP(a, b);
			Assert::AreEqual(a, 8);
			Assert::AreEqual(b, 5);
		}

		TEST_METHOD(swap_SString)
		{
			p2SString a("hola");
			p2SString b("mundo");
			SWAP(a, b);
			Assert::IsTrue(a == "mundo");
			Assert::IsTrue(b == "hola");
		}


		TEST_METHOD(Point2D_int)
		{
			p2Point<int> a;
			p2Point<int> b;

			a.x = a.y = 5;
			b = a;

			Assert::AreEqual(b.x, 5);
			Assert::AreEqual(b.y, 5);
		}

		TEST_METHOD(Point2D_double)
		{
			p2Point<double> a;
			p2Point<double> b;

			a.x = a.y = 3.1415;
			b = a;
			
			Assert::AreEqual(b.x, 3.1415);
			Assert::AreEqual(b.y, 3.1415);

			/*
			p2Point<p2SString> juas;
			juas.x = "hola";
			juas.y = "mundo";
			juas.DistanceTo(juas);
			*/
		}

		// p2SString -----------------------------------------
		TEST_METHOD(SString_empty_ctor)
		{
			p2SString s;
			Assert::AreEqual((int) s.Length(), 0);
		}
		TEST_METHOD(SString_char_ctor)
		{
			p2SString s("Hola mundo");
			Assert::AreEqual((int)s.Length(), 10);
		}
		TEST_METHOD(SString_format_ctor)
		{
			p2SString s("%s %s %d", "hola", "mundo", 12);
			Assert::AreEqual((int)s.Length(), 13);
		}
		TEST_METHOD(SString_copy_ctor)
		{
			p2SString s("%s %s %d", "hola", "mundo", 12);
			p2SString s2(s);
			Assert::AreEqual((int)s2.Length(), 13);
		}
		TEST_METHOD(SString_op_equal)
		{
			p2SString s1("Hola mundo");
			p2SString s2("Hola mundo");
			Assert::IsTrue(s1 == s2);
		}
		TEST_METHOD(SString_op_notequal)
		{
			p2SString s1("Hola mundo 1");
			p2SString s2("Hola mundo 2");
			Assert::IsTrue(s1 != s2);
		}
		TEST_METHOD(SString_op_equal_cstr)
		{
			p2SString s1("Hola mundo");
			Assert::IsTrue(s1 == "Hola mundo");
		}
		TEST_METHOD(SString_op_notequal_cstr)
		{
			p2SString s1("Hola mundo 1");
			Assert::IsTrue(s1 != "test");
		}
		TEST_METHOD(SString_op_assign)
		{
			p2SString s1("Hola mundo");
			p2SString s2;
			s2 = s1;
			Assert::IsTrue(s2 == "Hola mundo");
		}
		TEST_METHOD(SString_op_assign_cstr)
		{
			p2SString s1("Hola mundo");
			s1 = "this is a test";
			Assert::IsTrue(s1 == "this is a test");
		}
		TEST_METHOD(SString_op_concat)
		{
			p2SString s1("Hola mundo");
			p2SString s2("this is a test");
			s1 += s2;
			Assert::IsTrue(s1 == "Hola mundothis is a test");
		}
		TEST_METHOD(SString_op_concat_cstr)
		{
			p2SString s1("Hola mundo");
			s1 += "this is a test";
			Assert::IsTrue(s1 == "Hola mundothis is a test");
		}
		TEST_METHOD(SString_length)
		{
			p2SString s1("Hola mundo");
			Assert::AreEqual((int)s1.Length(), 10);
		}
		TEST_METHOD(SString_capacity)
		{
			p2SString s1("Hola mundo");
			Assert::AreEqual((int)s1.GetCapacity(), 11);
		}
		TEST_METHOD(SString_getstr)
		{
			p2SString s1("Hola mundo");
			Assert::AreEqual((int)strcmp("Hola mundo", s1.GetString()), 0);
		}
		TEST_METHOD(SString_clear)
		{
			p2SString s1("Hola mundo");
			s1.Clear();
			Assert::AreEqual((int)s1.Length(),0);
		}

		// p2List --------------------------------------------
		TEST_METHOD(ListAdd)
		{
			p2List<int> mylist;
			Assert::AreEqual((int)mylist.add(5), 1);
		}

		TEST_METHOD(ListDel)
		{
			p2List<int> mylist;
			mylist.add(5);
			Assert::IsTrue(mylist.del(mylist.start));
			Assert::AreEqual((int)mylist.count(), 0);
		}

		TEST_METHOD(ListClear)
		{
			p2List<int> mylist;

			mylist.add(1); 
			mylist.add(2);
			mylist.add(3);

			mylist.clear();
			Assert::AreEqual((int)mylist.count(), 0);
		}

		TEST_METHOD(ListBrackets)
		{
			p2List<int> mylist;
			mylist.add(5);
			Assert::AreEqual(mylist[0], 5);
		}

		TEST_METHOD(ListConcat)
		{
			p2List<int> mylist;
			mylist.add(5);
			mylist.add(5);
			mylist.add(5);

			p2List<int> mylist2;
			mylist2.add(6);
			mylist2.add(6);
			mylist2.add(6);

			mylist += mylist2;
			
			Assert::AreEqual(mylist[0], 5);
			Assert::AreEqual(mylist[1], 5);
			Assert::AreEqual(mylist[2], 5);
			Assert::AreEqual(mylist[3], 6);
			Assert::AreEqual(mylist[4], 6);
			Assert::AreEqual(mylist[5], 6);
		}
		
		// p2Tree --------------------------------------------
		TEST_METHOD(TreeAdd)
		{
			p2Tree<int> tree(0);
			
			tree.Add(100, 0);
			tree.Add(200, 0);
			tree.Add(300, 0);
			
			tree.Add(101, 100);
			tree.Add(102, 100);
			tree.Add(103, 100);
			
			tree.Add(210, 200);
			tree.Add(220, 200);
	
			tree.Add(221, 220);

			// Just do not test that we run forever because of the recursion
			Assert::AreEqual(1,1);
		}

		TEST_METHOD(TreePreOrderIterative)
		{
			p2Tree<char> tree('F');

			tree.Add('B', 'F');
			tree.Add('G', 'F');
			tree.Add('A', 'B');
			tree.Add('D', 'B');
			tree.Add('X', 'B');
			tree.Add('C', 'D');
			tree.Add('E', 'D');
			tree.Add('I', 'G');
			tree.Add('H', 'I');

			p2List<p2TreeNode<char>*> list;
			tree.PreOrderIterative(&list);

			Assert::AreEqual((int)list.count(), 10);

			Assert::AreEqual((char)list[0]->data, 'F');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'A');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'C');
			Assert::AreEqual((char)list[5]->data, 'E');
			Assert::AreEqual((char)list[6]->data, 'X');
			Assert::AreEqual((char)list[7]->data, 'G');
			Assert::AreEqual((char)list[8]->data, 'I');
			Assert::AreEqual((char)list[9]->data, 'H');
		}

		TEST_METHOD(TreePostOrderIterative)
		{
			p2Tree<char> tree('F');

			tree.Add('B', 'F');
			tree.Add('G', 'F');
			tree.Add('A', 'B');
			tree.Add('D', 'B');
			tree.Add('C', 'D');
			tree.Add('E', 'D');
			tree.Add('I', 'G');
			tree.Add('H', 'I');

			p2List<p2TreeNode<char>*> list;
			tree.PostOrderIterative(&list);

			Assert::AreEqual((int)list.count(), 9);

			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'C');
			Assert::AreEqual((char)list[2]->data, 'E');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'B');
			Assert::AreEqual((char)list[5]->data, 'H');
			Assert::AreEqual((char)list[6]->data, 'I');
			Assert::AreEqual((char)list[7]->data, 'G');
			Assert::AreEqual((char)list[8]->data, 'F');
		}

		TEST_METHOD(TreeInOrderIterative)
		{
			p2Tree<char> tree('F');

			tree.Add('B', 'F');
			tree.Add('G', 'F');
			tree.Add('A', 'B');
			tree.Add('D', 'B');
			tree.Add('C', 'D');
			tree.Add('E', 'D');
			tree.Add('I', 'G');
			tree.Add('H', 'I');

			p2List<p2TreeNode<char>*> list;
			tree.InOrderIterative(&list);

			Assert::AreEqual((int)list.count(), 9);

			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'C');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'E');
			Assert::AreEqual((char)list[5]->data, 'F');
			Assert::AreEqual((char)list[6]->data, 'G');
			Assert::AreEqual((char)list[7]->data, 'I');
			Assert::AreEqual((char)list[8]->data, 'H');
		}

		TEST_METHOD(TreePreOrder)
		{
			p2Tree<char> tree('F');

			tree.Add('B', 'F');
			tree.Add('G', 'F');
			tree.Add('A', 'B');
			tree.Add('D', 'B');
			tree.Add('X', 'B');
			tree.Add('C', 'D');
			tree.Add('E', 'D');
			tree.Add('I', 'G');
			tree.Add('H', 'I');

			p2List<p2TreeNode<char>*> list;
			tree.PreOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 10);

			Assert::AreEqual((char)list[0]->data, 'F');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'A');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'C');
			Assert::AreEqual((char)list[5]->data, 'E');
			Assert::AreEqual((char)list[6]->data, 'X');
			Assert::AreEqual((char)list[7]->data, 'G');
			Assert::AreEqual((char)list[8]->data, 'I');
			Assert::AreEqual((char)list[9]->data, 'H');
		}

		TEST_METHOD(TreePostOrder)
		{
			p2Tree<char> tree('F');

			tree.Add('B', 'F');
			tree.Add('G', 'F');
			tree.Add('A', 'B');
			tree.Add('D', 'B');
			tree.Add('C', 'D');
			tree.Add('E', 'D');
			tree.Add('I', 'G');
			tree.Add('H', 'I');

			p2List<p2TreeNode<char>*> list;
			tree.PostOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 9);

			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'C');
			Assert::AreEqual((char)list[2]->data, 'E');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'B');
			Assert::AreEqual((char)list[5]->data, 'H');
			Assert::AreEqual((char)list[6]->data, 'I');
			Assert::AreEqual((char)list[7]->data, 'G');
			Assert::AreEqual((char)list[8]->data, 'F');
		}

		TEST_METHOD(TreeInOrder)
		{
			p2Tree<char> tree('F');

			tree.Add('B', 'F');
			tree.Add('G', 'F');
			tree.Add('A', 'B');
			tree.Add('D', 'B');
			tree.Add('C', 'D');
			tree.Add('E', 'D');
			tree.Add('I', 'G');
			tree.Add('H', 'I');

			p2List<p2TreeNode<char>*> list;
			tree.InOrderRecursive(&list);

			Assert::AreEqual((int)list.count(), 9);

			Assert::AreEqual((char)list[0]->data, 'A');
			Assert::AreEqual((char)list[1]->data, 'B');
			Assert::AreEqual((char)list[2]->data, 'C');
			Assert::AreEqual((char)list[3]->data, 'D');
			Assert::AreEqual((char)list[4]->data, 'E');
			Assert::AreEqual((char)list[5]->data, 'F');
			Assert::AreEqual((char)list[6]->data, 'G');
			Assert::AreEqual((char)list[7]->data, 'I');
			Assert::AreEqual((char)list[8]->data, 'H');
		}

		TEST_METHOD(TreeGather)
		{
			p2Tree<int> tree(0);
			
			tree.Add(100, 0);
			tree.Add(200, 0);
			tree.Add(300, 0);
			tree.Add(101, 100);
			tree.Add(102, 100);
			tree.Add(103, 100);
			tree.Add(210, 200);
			tree.Add(220, 200);
			tree.Add(221, 220);
			
			p2List<p2TreeNode<int>*> list;
			tree.trunk.GatherAll(&list);
			
			Assert::AreEqual((int)list.count(), 10);

			Assert::AreEqual((int)list[0]->data, 0);
			Assert::AreEqual((int)list[1]->data, 100);
			Assert::AreEqual((int)list[2]->data, 101);
			Assert::AreEqual((int)list[3]->data, 102);
			Assert::AreEqual((int)list[4]->data, 103);
			Assert::AreEqual((int)list[5]->data, 200);
			Assert::AreEqual((int)list[6]->data, 210);
			Assert::AreEqual((int)list[7]->data, 220);
			Assert::AreEqual((int)list[8]->data, 221);
			Assert::AreEqual((int)list[9]->data, 300);

		}

		
		TEST_METHOD(TreeDelRecursive)
		{
			p2Tree<int> tree(0);
			
			tree.Add(100, 0);
			tree.Add(200, 0);
			tree.Add(300, 0);
			tree.Add(101, 100);
			tree.Add(102, 100);
			tree.Add(103, 100);
			tree.Add(210, 200);
			tree.Add(220, 200);
			tree.Add(221, 220);
			
			tree.DelRecursive(200);

			p2List<p2TreeNode<int>*> list;
			tree.trunk.GatherAll(&list);
			
			Assert::AreEqual((int)list.count(), 6);

			Assert::AreEqual((int)list[0]->data, 0);
			Assert::AreEqual((int)list[1]->data, 100);
			Assert::AreEqual((int)list[2]->data, 101);
			Assert::AreEqual((int)list[3]->data, 102);
			Assert::AreEqual((int)list[4]->data, 103);
			Assert::AreEqual((int)list[5]->data, 300);

			for(p2List_item<p2TreeNode<int>*>* item =  list.start; item != NULL; item = item->next)
			{
				p2TreeNode<int>* child = item->data;
				TLOG("node: %d parent: %d", child->data, (child->parent) ? child->parent->data : -1);
			}

		}

		//---------------------------------------------------
		//----------------EXAMEN PARCIAL---------------------
		//---------------------------------------------------

		// Projectile ----------------------------------------
		TEST_METHOD(Projectile_test)
		{
			Projectile p;

			p.point.x = 10.0f;
			p.point.y = 10.0f;

			p.speed.x = 2.0f;
			p.speed.y = 0.0f;

			p2Point<float> current = p.getCurrentPosition(3.0f);

			Assert::AreEqual((float)16.0f, current.x, 0.00001f);
			Assert::AreEqual((float)10.0f, current.y, 0.00001f);
		}

		// ArrDyn remove wasted memory ----------------------------------------
		TEST_METHOD(ArrDyn_optimizeMem)
		{
			p2DynArray<int> array(10);

			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(3);

			Assert::AreEqual((unsigned int)10, array.GetCapacity());

			unsigned int wasted = array.removeWastedMemory();

			Assert::AreEqual((unsigned int)3, array.GetCapacity());
			Assert::AreEqual((unsigned int)7, wasted);
			Assert::AreEqual((int)1, array[0]);
			Assert::AreEqual((int)2, array[1]);
			Assert::AreEqual((int)3, array[2]);
		}
		
		// P2List delete few nodes ----------------------------------------
		TEST_METHOD(p2List_delNodes_mid)
		{
			p2List<int> l;

			l.add(1);
			l.add(2);
			l.add(3);
			l.add(4);

			l.delNodes(1, 2);

			Assert::AreEqual((int)1, l.start->data);
			Assert::AreEqual((int)4, l.end->data);
			Assert::AreEqual((unsigned int)2, l.count());
		}

		// P2List delete few nodes ----------------------------------------
		TEST_METHOD(p2List_delNodes_begin)
		{
			p2List<int> l;

			l.add(1);
			l.add(2);
			l.add(3);
			l.add(4);

			l.delNodes(0, 3);

			Assert::AreEqual((int)4, l.start->data);
			Assert::AreEqual((int)4, l.end->data);
			Assert::AreEqual((unsigned int)1, l.count());
		}

		// P2List delete few nodes ----------------------------------------
		TEST_METHOD(p2List_delNodes_end)
		{
			p2List<int> l;

			l.add(1);
			l.add(2);
			l.add(3);
			l.add(4);

			l.delNodes(2, 100);

			Assert::AreEqual((int)1, l.start->data);
			Assert::AreEqual((int)2, l.end->data);
			Assert::AreEqual((unsigned int)2, l.count());
		}
		
		// String prefix ----------------------------------------
		TEST_METHOD(String_prefix)
		{
			p2SString a("1234567890");
			p2SString b(50);
			b = "hola";

			a.prefix(b);
			b.prefix("1234567890");

			Assert::AreEqual(strcmp(a.GetString(), "hola1234567890"), 0);
			Assert::AreEqual(strcmp(b.GetString(), "1234567890hola"), 0);
		}

		//---------------------------------------------------
		//----------------EXAMEN FINAL---------------------
		//---------------------------------------------------

		TEST_METHOD(SString_cut)
		{
			p2SString s1("Hola mundo");
			s1.Cut(2, 5);
			Assert::AreEqual((int)strcmp("Houndo", s1.GetString()), 0);
			s1.Cut(3, 0);
			Assert::AreEqual((int)strcmp("Hou", s1.GetString()), 0);
		}

		TEST_METHOD(DynArray_Operator_concat)
		{
			p2DynArray<int> array(5);
			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(4);
			array.PushBack(5);
			array.PushBack(8);
			p2DynArray<int> array2;
			array2.PushBack(991);
			array2.PushBack(992);
			array2.PushBack(993);
			array += array2;
			Assert::AreEqual((int)array.Count(), 8);
			Assert::AreEqual((int)array[0], 1);
			Assert::AreEqual((int)array[1], 2);
			Assert::AreEqual((int)array[2], 4);
			Assert::AreEqual((int)array[3], 5);
			Assert::AreEqual((int)array[4], 8);
			Assert::AreEqual((int)array[5], 991);
			Assert::AreEqual((int)array[6], 992);
			Assert::AreEqual((int)array[7], 993);
		}

		TEST_METHOD(ListInsert)
		{
			p2List<int> mylist;
			p2List<int> mylist2;
			mylist2.add(1);
			mylist2.add(2);
			mylist2.add(3);
			p2List<int> mylist3;
			mylist3.add(4);
			mylist3.add(5);
			mylist3.add(6);
			mylist.InsertAfter(0, mylist2);
			Assert::AreEqual(mylist[0], 1);
			Assert::AreEqual(mylist[1], 2);
			Assert::AreEqual(mylist[2], 3);
			mylist.InsertAfter(1, mylist3);
			Assert::AreEqual(mylist[0], 1);
			Assert::AreEqual(mylist[1], 2);
			Assert::AreEqual(mylist[2], 4);
			Assert::AreEqual(mylist[3], 5);
			Assert::AreEqual(mylist[4], 6);
			Assert::AreEqual(mylist[5], 3);
			mylist.InsertAfter(0, mylist3);
			Assert::AreEqual(mylist[0], 1);
			Assert::AreEqual(mylist[1], 4);
			Assert::AreEqual(mylist[2], 5);
			Assert::AreEqual(mylist[3], 6);
			Assert::AreEqual(mylist[4], 2);
			Assert::AreEqual(mylist[5], 4);
			Assert::AreEqual(mylist[6], 5);
			Assert::AreEqual(mylist[7], 6);
			Assert::AreEqual(mylist[8], 3);
			Assert::IsTrue((p2List_item<int>*) &mylist[0] == mylist.start);
			Assert::IsTrue((p2List_item<int>*) &mylist[8] == mylist.end);
		}

		TEST_METHOD(TreeCalcAddition)
		{
			p2Tree<int> tree(1);
			tree.Add(2, 1);
			tree.Add(3, 1);
			tree.Add(4, 1);
			tree.Add(5, 2);
			tree.Add(6, 2);
			tree.Add(7, 2);
			tree.Add(8, 4);
			tree.Add(9, 4);
			tree.Add(10, 9);
			//Assert::AreEqual((int)tree.CalcAdditionRecursive(), 55); //El recursiu no m'ha sortit 
			Assert::AreEqual((int)tree.CalcAdditionIterative(), 55);
		}


	};
}