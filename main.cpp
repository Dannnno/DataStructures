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
	testList.append(1);
	testList.append(2);
	testList.append(3);
	testList.append(4);
	cout << testList << endl;

	exit(0);
}