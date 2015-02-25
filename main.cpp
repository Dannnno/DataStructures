#include <iostream>
#include <cstdlib>

#include "linkedlist/listnode.hpp"
#include "linkedlist/linkedlist.hpp"


using namespace std;

int main()
{
	ListNode<int> testNode1(1);
	cout << testNode1 << endl;

	int initarr[5] = {1, 2, 3, 4, 5};
	LinkedList<int> testList(initarr, 5);
	LinkedList<int> testList2;
	testList2.append(1);
	testList2.append(2);
	testList2.append(3);
	testList2.append(4);
	cout << testList << endl;
	cout << testList2 << endl;

	exit(0);
}