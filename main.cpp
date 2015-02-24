#include <iostream>
#include <cstdlib>

#include "linkedlist/listnode.hpp"
#include "linkedlist/linkedlist.hpp"


using namespace std;

int main()
{
	ListNode<int> testNode1(1);
	cout << testNode1 << endl;

	LinkedList<int> testList;
	testList.appendRight(1);
	testList.appendRight(2);
	testList.appendRight(3);
	testList.appendRight(4);
	cout << testList << endl;

	exit(0);
}