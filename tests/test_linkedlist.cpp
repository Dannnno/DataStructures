#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "../linkedlist/linkedlist.hpp"

TEST(LinkedListTest, constructor) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);
	EXPECT_EQ(false, list.isEmpty());
	EXPECT_EQ(5, list.size());
}

TEST(LinkedListTest, empty) {
	LinkedList<int> list1;
	LinkedList<int> list2;
	list2.append(1);

	EXPECT_EQ(true, list1.isEmpty());
	EXPECT_EQ(false, list2.isEmpty());
}

TEST(LinkedListTest, size) {
	LinkedList<int> list1;
	LinkedList<int> list2;
	list2.append(1);
	list2.append(2);

	EXPECT_EQ(0, list1.size());
	EXPECT_EQ(2, list2.size());
}

TEST(LinkedListTest, LengthOne) {
	LinkedList<int> list;
	list.append(1);

	EXPECT_EQ(1, list.getHead());
	EXPECT_EQ(1, list.getTail());
	EXPECT_EQ(list.getHead(), list.getTail());
}

TEST(LinkedListTest, LengthTwo) {
	LinkedList<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list.getHead());
	EXPECT_EQ(2, list.getTail());
	EXPECT_NE(list.getHead(), list.getTail());	
}

TEST(LinkedListTest, subscript) {
	LinkedList<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list[0]);
	EXPECT_EQ(2, list[1]);
}

TEST(LinkedListTest, stringLengthOne) {
	LinkedList<int> list;
	list.append(1);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1}", str);
}

TEST(LinkedListTest, stringLengthTwo) {
	LinkedList<int> list;
	list.append(1);
	list.append(2);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1, 2}", str);

}
