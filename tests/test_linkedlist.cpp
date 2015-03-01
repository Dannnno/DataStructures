#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "../structures/linkedlist.hpp"
#include "../exceptions.hpp"


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

	EXPECT_EQ("{1}\n", str);
}

TEST(LinkedListTest, stringLengthTwo) {
	LinkedList<int> list;
	list.append(1);
	list.append(2);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1, 2}\n", str);
}

TEST(LinkedListTest, popDefaultEmptyList) {
	LinkedList<int> list;

	EXPECT_THROW(list.pop(), IndexOutOfBoundsException);
}

TEST(LinkedListTest, popSpecificEmptyList) {
	LinkedList<int> list;

	EXPECT_THROW(list.pop(1), IndexOutOfBoundsException);
}

TEST(LinkedListTest, popDefaultNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);

	EXPECT_EQ(1, list.pop());
	EXPECT_EQ(4, list.size());
}

TEST(LinkedListTest, popSpecificNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);

	EXPECT_EQ(3, list.pop(2));
	EXPECT_EQ(4, list.size());
}

TEST(LinkedListTest, popOutOfRange) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);

	EXPECT_THROW(list.pop(5), IndexOutOfBoundsException);
}

TEST(LinkedListTest, removeDefaultEmptyList) {
	LinkedList<int> list;

	EXPECT_THROW(list.remove(), IndexOutOfBoundsException);
}

TEST(LinkedListTest, removeSpecificEmptyList) {
	LinkedList<int> list;

	EXPECT_THROW(list.remove(1), IndexOutOfBoundsException);
}

TEST(LinkedListTest, removeDefaultNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);
	list.remove();
	EXPECT_EQ(4, list.size());
}

TEST(LinkedListTest, removeSpecificNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);
	list.remove(2);
	EXPECT_EQ(4, list.size());
	EXPECT_EQ(4, list[2]);
}

TEST(LinkedListTest, removeOutOfRange) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);

	EXPECT_THROW(list.remove(5), IndexOutOfBoundsException);
}


TEST(LinkedListTest, insertEmpty) {
	LinkedList<int> list;
	list.insert(0, 1);

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(1, list[0]);
}

TEST(LinkedListTest, insertEmptyBad) {
	LinkedList<int> list;

	EXPECT_THROW(list.insert(1, 1), IndexOutOfBoundsException);
}

TEST(LinkedListTest, insertSingle) {
	LinkedList<int> list;
	list.append(1);
	list.insert(0, 2);

	EXPECT_EQ(2, list.size());
	EXPECT_EQ(2, list[0]);
}

TEST(LinkedListTest, insertMany) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);
	list.insert(3, 7);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(7, list[3]);
	EXPECT_EQ(3, list[2]);
	EXPECT_EQ(4, list[4]);
}

TEST(LinkedListTest, insertEnd) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);
	list.insert(5, 7);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(7, list[5]);
}

TEST(LinkedListTest, appendToEmpty) {
	LinkedList<int> list;
	list.append(1);

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(1, list[0]);
}

TEST(LinkedListTest, appendToOne) {
	LinkedList<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(2, list.size());
	EXPECT_EQ(2, list[1]);
}

TEST(LinkedListTest, appendToMany) {
	int initarray[5] = {1, 2, 3, 4, 5};
	LinkedList<int> list(initarray, 5);
	list.append(6);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(6, list[5]);
}