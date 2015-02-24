#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "../linkedlist/listnode.hpp"


TEST(ListNodeTest, getValue) {
	EXPECT_EQ(1, ListNode<int>(1).getValue());
	EXPECT_EQ(100, ListNode<int>(100).getValue());
}

TEST(ListNodeTest, getNext) {
	ListNode<int>* node1 = new ListNode<int>(1);
	ListNode<int>* node2 = new ListNode<int>(2);
	node1->setNext(node2);

	EXPECT_EQ(node2, node1->getNext());
	EXPECT_EQ(2, node1->getNext()->getValue());
	delete node1;
	delete node2;
}

TEST(ListNodeTest, nextConstructor) {
	ListNode<int>* node1 = new ListNode<int>(1);
	ListNode<int>* node2 = new ListNode<int>(2, node1);

	EXPECT_EQ(node1, node2->getNext());
	EXPECT_EQ(1, node2->getNext()->getValue());
	delete node1;
	delete node2;
}

TEST(ListNodeTest, setNext) {
	ListNode<int>* node1 = new ListNode<int>(1);
	ListNode<int>* node2 = new ListNode<int>(2, node1);
	ListNode<int>* node3 = new ListNode<int>(3);

	EXPECT_EQ(node1, node2->getNext());
	EXPECT_EQ(1, node2->getNext()->getValue());

	node2->setNext(node3);
	EXPECT_EQ(node3, node2->getNext());
	EXPECT_EQ(3, node2->getNext()->getValue());

	delete node1;
	delete node2;
	delete node3;
}

TEST(ListNodeTest, stream) {
	ListNode<int> node1(1);
	std::ostringstream stream;
	stream << node1;
	std::string str = stream.str();
	EXPECT_EQ("1", str);
}
