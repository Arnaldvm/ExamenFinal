#include "p2SString.h"
#include "p2DynArray.h"
#include "p2List.h"
#include "p2Tree.h"


int main(){

	/*p2SString s1("Hola mundo");
	s1.Cut(2, 5);
	//Assert::AreEqual((int)strcmp("Houndo", s1.GetString()), 0);
	s1.Cut(3, 0);
	//Assert::AreEqual((int)strcmp("Hou", s1.GetString()), 0);*/

	/*p2DynArray<int> array(5);
	array.PushBack(1);
	array.PushBack(2);
	array.PushBack(4);
	array.PushBack(5);
	array.PushBack(8);
	p2DynArray<int> array2;
	array2.PushBack(991);
	array2.PushBack(992);
	array2.PushBack(993);
	array += array2;*/

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
	//Assert::AreEqual(mylist[0], 1);
	//Assert::AreEqual(mylist[1], 2);
	//Assert::AreEqual(mylist[2], 3);
	mylist.InsertAfter(1, mylist3);
	//Assert::AreEqual(mylist[0], 1);
	//Assert::AreEqual(mylist[1], 2);
	//Assert::AreEqual(mylist[2], 4);
	//Assert::AreEqual(mylist[3], 5);
	//Assert::AreEqual(mylist[4], 6);
	//Assert::AreEqual(mylist[5], 3);
	mylist.InsertAfter(0, mylist3);
	//Assert::AreEqual(mylist[0], 1);
	//Assert::AreEqual(mylist[1], 4);
	//Assert::AreEqual(mylist[2], 5);
	//Assert::AreEqual(mylist[3], 6);
	//Assert::AreEqual(mylist[4], 2);
	//Assert::AreEqual(mylist[5], 4);
	//Assert::AreEqual(mylist[6], 5);
	//Assert::AreEqual(mylist[7], 6);
	//Assert::AreEqual(mylist[8], 3);
	//Assert::IsTrue((p2List_item<int>*) &mylist[0] == mylist.start);
	//Assert::IsTrue((p2List_item<int>*) &mylist[8] == mylist.end);

	/*p2Tree<int> tree(1);
	tree.Add(2, 1);
	tree.Add(3, 1);
	tree.Add(4, 1);
	tree.Add(5, 2);
	tree.Add(6, 2);
	tree.Add(7, 2);
	tree.Add(8, 4);
	tree.Add(9, 4);
	tree.Add(10, 9);
	//Assert::AreEqual((int)tree.CalcAdditionRecursive(), 55);
	tree.CalcAdditionIterative();*/

}