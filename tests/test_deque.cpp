#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "../structures/deque.hpp"
#include "../exceptions.hpp"


TEST(DequeTest, constructor) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	EXPECT_EQ(false, list.isEmpty());
	EXPECT_EQ(5, list.size());
}

TEST(DequeTest, empty) {
	Deque<int> list1;
	Deque<int> list2;
	list2.append(1);

	EXPECT_EQ(true, list1.isEmpty());
	EXPECT_EQ(false, list2.isEmpty());
}

TEST(DequeTest, size) {
	Deque<int> list1;
	Deque<int> list2;
	list2.append(1);
	list2.append(2);

	EXPECT_EQ(0, list1.size());
	EXPECT_EQ(2, list2.size());
}

TEST(DequeTest, LengthOne) {
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(1, list.getHead());
	EXPECT_EQ(1, list.getTail());
	EXPECT_EQ(list.getHead(), list.getTail());
}

TEST(DequeTest, LengthTwo) {
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list.getHead());
	EXPECT_EQ(2, list.getTail());
	EXPECT_NE(list.getHead(), list.getTail());	
}

TEST(DequeTest, subscript) {
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list[0]);
	EXPECT_EQ(2, list[1]);
}

TEST(DequeTest, stringLengthOne) {
	Deque<int> list;
	list.append(1);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1}\n", str);
	EXPECT_EQ(str.length(), 4);
}

TEST(DequeTest, stringLengthTwo) {
	Deque<int> list;
	list.append(1);
	list.append(2);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1, 2}\n", str);
	EXPECT_EQ(str.length(), 7);
}

TEST(DequeTest, popDefaultEmptyList) {
	Deque<int> list;

	EXPECT_THROW(list.pop(), IndexOutOfBoundsException);
}

TEST(DequeTest, popSpecificEmptyList) {
	Deque<int> list;

	EXPECT_THROW(list.pop(1), IndexOutOfBoundsException);
}

TEST(DequeTest, popDefaultNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_EQ(1, list.pop());
	EXPECT_EQ(4, list.size());
}

TEST(DequeTest, popSpecificNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_EQ(3, list.pop(2));
	EXPECT_EQ(4, list.size());
}

TEST(DequeTest, popOutOfRange) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_THROW(list.pop(5), IndexOutOfBoundsException);
}

TEST(DequeTest, removeDefaultEmptyList) {
	Deque<int> list;

	EXPECT_THROW(list.remove(), IndexOutOfBoundsException);
}

TEST(DequeTest, removeSpecificEmptyList) {
	Deque<int> list;

	EXPECT_THROW(list.remove(1), IndexOutOfBoundsException);
}

TEST(DequeTest, removeDefaultNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.remove();
	EXPECT_EQ(4, list.size());
}

TEST(DequeTest, removeSpecificNonEmptyList) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.remove(2);
	EXPECT_EQ(4, list.size());
	EXPECT_EQ(4, list[2]);
}

TEST(DequeTest, removeOutOfRange) {
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_THROW(list.remove(5), IndexOutOfBoundsException);
}
