#include <cassert>
#include <sstream>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#include "../structures/deque.hpp"
#include "../exceptions.hpp"


TEST(DequeTest, constructor) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	EXPECT_EQ(false, list.isEmpty());
	EXPECT_EQ(5, list.size());
}

TEST(DequeTest, copyConstructor)
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	Deque<int> copy(list);

	for (size_t i = 0; i < 5; ++i)
		EXPECT_EQ(list[i], copy[i]);

	copy[3] = 1;

	EXPECT_NE(list[3], copy[3]);
}

TEST(DequeTest, moveConstructor)
{
	int initArray[5] = {1, 2, 3, 4, 5};
	Deque<int> mlist{initArray, 5};
	Deque<int> list{std::move(mlist)};

	EXPECT_EQ(list.size(), 5);

	for (size_t i = 0; i < 5; ++i)
		EXPECT_EQ(list[i], initArray[i]);
}

TEST(DequeTest, assignment)
{
	int initArray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initArray, 5);
	Deque<int> list2;
	list2 = list;

	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(list[i], list2[i]);
	}

	list[3] = 1;
	EXPECT_NE(list[3], list2[3]);
	EXPECT_EQ(list[3], 1);
	EXPECT_EQ(list2[3], 4);
}

TEST(DequeTest, empty) 
{
	Deque<int> list1;
	Deque<int> list2;
	list2.append(1);

	EXPECT_EQ(true, list1.isEmpty());
	EXPECT_EQ(false, list2.isEmpty());
}

TEST(DequeTest, size) 
{
	Deque<int> list1;
	Deque<int> list2;
	list2.append(1);
	list2.append(2);

	EXPECT_EQ(0, list1.size());
	EXPECT_EQ(2, list2.size());
}

TEST(DequeTest, LengthOne) 
{
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(1, list.getHead());
	EXPECT_EQ(1, list.getTail());
	EXPECT_EQ(list.getHead(), list.getTail());
}

TEST(DequeTest, LengthTwo) 
{
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list.getHead());
	EXPECT_EQ(2, list.getTail());
	EXPECT_NE(list.getHead(), list.getTail());	
}

TEST(DequeTest, subscriptEmptyList) 
{
	Deque<int> list;

	EXPECT_THROW(list[0], IndexOutOfBoundsException);
}

TEST(DequeTest, subscriptValidList) 
{
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list[0]);
	EXPECT_EQ(2, list[1]);
}

TEST(DequeTest, subscriptOutOfBounds)
{
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_THROW(list[2], IndexOutOfBoundsException);
}

TEST(DequeTest, subscriptAssignment)
{
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(1, list[0]);
	list[0] = 5;
	EXPECT_EQ(5, list[0]);
}

TEST(DequeTest, stringLengthOne) 
{
	Deque<int> list;
	list.append(1);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1}\n", str);
}

TEST(DequeTest, stringLengthTwo) 
{
	Deque<int> list;
	list.append(1);
	list.append(2);

	std::ostringstream stream;
	stream << list;
	std::string str = stream.str();

	EXPECT_EQ("{1, 2}\n", str);
}

TEST(DequeTest, popDefaultEmptyList) 
{
	Deque<int> list;

	EXPECT_THROW(list.pop(), IndexOutOfBoundsException);
}

TEST(DequeTest, popSpecificEmptyList) 
{
	Deque<int> list;

	EXPECT_THROW(list.pop(1), IndexOutOfBoundsException);
}

TEST(DequeTest, popDefaultNonEmptyList) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_EQ(1, list.pop());
	EXPECT_EQ(4, list.size());
}

TEST(DequeTest, popSpecificNonEmptyList) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_EQ(3, list.pop(2));
	EXPECT_EQ(4, list.size());
}

TEST(DequeTest, popOutOfRange) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_THROW(list.pop(5), IndexOutOfBoundsException);
}

TEST(DequeTest, removeDefaultEmptyList) 
{
	Deque<int> list;

	EXPECT_THROW(list.remove(), IndexOutOfBoundsException);
}

TEST(DequeTest, removeSpecificEmptyList) 
{
	Deque<int> list;

	EXPECT_THROW(list.remove(1), IndexOutOfBoundsException);
}

TEST(DequeTest, removeDefaultNonEmptyList) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.remove();
	EXPECT_EQ(4, list.size());
}

TEST(DequeTest, removeSpecificNonEmptyList) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.remove(2);
	EXPECT_EQ(4, list.size());
	EXPECT_EQ(4, list[2]);
}

TEST(DequeTest, removeOutOfRange) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);

	EXPECT_THROW(list.remove(5), IndexOutOfBoundsException);
}


TEST(DequeTest, insertEmpty) 
{
	Deque<int> list;
	list.insert(0, 1);

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(1, list[0]);
}

TEST(DequeTest, insertEmptyBad) 
{
	Deque<int> list;

	EXPECT_THROW(list.insert(1, 1), IndexOutOfBoundsException);
}

TEST(DequeTest, insertSingle) 
{
	Deque<int> list;
	list.append(1);
	list.insert(0, 2);

	EXPECT_EQ(2, list.size());
	EXPECT_EQ(2, list[0]);
}

TEST(DequeTest, insertMany) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.insert(3, 7);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(7, list[3]);
	EXPECT_EQ(3, list[2]);
	EXPECT_EQ(4, list[4]);
}

TEST(DequeTest, insertEnd) 
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.insert(5, 7);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(7, list[5]);
}

TEST(DequeTest, appendToEmpty) 
{
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(1, list[0]);
}

TEST(DequeTest, appendToOne) 
{
	Deque<int> list;
	list.append(1);
	list.append(2);

	EXPECT_EQ(2, list.size());
	EXPECT_EQ(2, list[1]);
}

TEST(DequeTest, appendToMany)
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.append(6);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(6, list[5]);
}

TEST(DequeTest, appendLeftToEmpty) 
{
	Deque<int> list;
	list.appendLeft(1);

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(1, list[0]);
}

TEST(DequeTest, appendLeftToOne) 
{
	Deque<int> list;
	list.appendLeft(1);
	list.appendLeft(2);

	EXPECT_EQ(2, list.size());
	EXPECT_EQ(2, list[0]);
}

TEST(DequeTest, appendLeftToMany)
{
	int initarray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initarray, 5);
	list.appendLeft(6);

	EXPECT_EQ(6, list.size());
	EXPECT_EQ(6, list[0]);
}

TEST(DequeTest, forEach) 
{
	int initArray[5] = {1, 2, 3, 4, 5};
	Deque<int> list(initArray, 5);

	int i = 0;
	for (int node : list) {
		EXPECT_EQ(node, initArray[i]);
		++i;
	}
}

TEST(DISABLED_DequeTest, sortEmptyList) 
{
	Deque<int> list;

	EXPECT_EQ(list.size(), 0);
	list.sort();
	EXPECT_EQ(list.size(), 0);
}

TEST(DISABLED_DequeTest, sortedEmptyList) 
{
	Deque<int> list;

	EXPECT_EQ(list.size(), 0);
	Deque<int> copy = list.sorted();
	EXPECT_EQ(list, copy);
	EXPECT_EQ(copy.size(), 0);
}

TEST(DISABLED_DequeTest, sortOneItemList) 
{
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.getHead(), 1);
	list.sort();
	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.getHead(), 1);
}

TEST(DISABLED_DequeTest, sortedOneItemList) 
{
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.getHead(), 1);
	Deque<int> copy = list.sorted();
	EXPECT_EQ(copy.size(), 1);
	EXPECT_EQ(copy.getHead(), 1);
	EXPECT_EQ(list, copy);
}

TEST(DISABLED_DequeTest, sortManyItemsList) 
{
	int initArray[5] = {3, 2, 5, 1, 7};
	int sortedArray[5] = {1, 2, 3, 5, 7};
	Deque<int> list(initArray, 5);
	list.sort();

	EXPECT_EQ(list.size(), 5);
	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(sortedArray[i], list[i]);
	}
}

TEST(DISABLED_DequeTest, sortedManyItemsList) 
{
	int initArray[5] = {3, 2, 5, 1, 7};
	int sortedArray[5] = {1, 2, 3, 5, 7};
	Deque<int> list(initArray, 5);
	Deque<int> copy = list.sorted();

	EXPECT_EQ(list.size(), 5);
	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(sortedArray[i], copy[i]);
	}
	EXPECT_NE(copy, list);
}

TEST(DequeTest, reverseEmptyList) 
{
	Deque<int> list;

	EXPECT_EQ(list.size(), 0);
	list.reverse();
	EXPECT_EQ(list.size(), 0);
}

TEST(DequeTest, reversedEmptyList)
{
	Deque<int> list;

	EXPECT_EQ(list.size(), 0);
	Deque<int> copy = list.reversed();
	EXPECT_EQ(list, copy);
	EXPECT_EQ(copy.size(), 0);
}

TEST(DequeTest, reverseOneItemList) 
{
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.getHead(), 1);
	list.reverse();
	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.getHead(), 1);
}

TEST(DequeTest, reversedOneItemList) 
{
	Deque<int> list;
	list.append(1);

	EXPECT_EQ(list.size(), 1);
	EXPECT_EQ(list.getHead(), 1);
	Deque<int> copy = list.reversed();
	EXPECT_EQ(copy.size(), 1);
	EXPECT_EQ(copy.getHead(), 1);
	EXPECT_EQ(list, copy);
}

TEST(DequeTest, reverseManyItemsList) 
{
	int initArray[5] = {3, 2, 5, 1, 7};
	int reversedArray[5] = {7, 1, 5, 2, 3};
	Deque<int> list(initArray, 5);
	list.reverse();

	EXPECT_EQ(list.size(), 5);
	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(reversedArray[i], list[i]);
	}
}

TEST(DequeTest, reversedManyItemsList) 
{
	int initArray[5] = {3, 2, 5, 1, 7};
	int reversedArray[5] = {7, 1, 5, 2, 3};
	Deque<int> list(initArray, 5);
	Deque<int> copy = list.reversed();

	EXPECT_EQ(list.size(), 5);
	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(reversedArray[i], copy[i]);
	}
	EXPECT_NE(copy, list);
}

TEST(DequeTest, toArrayEmpty)
{
	Deque<int> list;
	EXPECT_THROW(list.toArray(), IndexOutOfBoundsException);
}

TEST(DequeTest, toArrayOne)
{
	Deque<int> list;
	list.append(1);
	int* newArray = list.toArray();
	EXPECT_EQ(1, newArray[0]);
	delete [] newArray;
}

TEST(DequeTest, toArrayMany)
{
	int initArray[5] = {3, 2, 5, 1, 7};
	Deque<int> list(initArray, 5);

	int* resultArray = list.toArray();
	for (size_t i = 0; i < 5; ++i) 
		EXPECT_EQ(initArray[i], resultArray[i]);
	delete [] resultArray;
}

TEST(DequeTest, swap)
{
	int initArray1[5] = {1, 2, 3, 4, 5};
	int initArray2[3] = {6, 7, 8};
	Deque<int> list1{initArray1, 5};
	Deque<int> list2{initArray2, 3};

	swap(list1, list2);

	EXPECT_EQ(list1.size(), 3);
	EXPECT_EQ(list2.size(), 5);

	for (size_t i = 0; i < 3; ++i) 
		EXPECT_EQ(list1[i], initArray2[i]);

	for (size_t i = 0; i < 5; ++i)
		EXPECT_EQ(list2[i], initArray1[i]);
}

TEST(DequeTest, additionList)
{
	int initArray1[5] = {1, 2, 3, 4, 5};
	int initArray2[3] = {6, 7, 8};
	int resultArray[8] = {1, 2, 3, 4, 5, 6, 7, 8};

	Deque<int> list1{initArray1, 5};
	Deque<int> list2{initArray2, 3};

	Deque<int> result = list1 + list2;

	EXPECT_EQ(list1.size(), 5);
	EXPECT_EQ(list2.size(), 3);

	for (size_t i = 0; i < 5; ++i) 
		EXPECT_EQ(list1[i], initArray1[i]);

	for (size_t i = 0; i < 3; ++i)
		EXPECT_EQ(list2[i], initArray2[i]);

	EXPECT_EQ(result.size(), 8);

	for (size_t i = 0; i < 8; ++i)
		EXPECT_EQ(result[i], resultArray[i]);

	result[3] = 9;

	EXPECT_EQ(list1[3], 4);
}

TEST(DequeTest, multiplicationZero)
{
	int initArray[5] = {1, 2, 3, 4, 5};
	Deque<int> list{initArray, 5};
	Deque<int> result = list * 0;

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(result.size(), 5);

	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(list[i], result[i]);
		EXPECT_EQ(result[i], initArray[i]);
	}

	result[3] = 9;

	EXPECT_EQ(list[3], 4);
}

TEST(DequeTest, multiplicationOne)
{
	int initArray[5] = {1, 2, 3, 4, 5};
	Deque<int> list{initArray, 5};
	Deque<int> result = list * 1;

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(result.size(), 5);

	for (size_t i = 0; i < 5; ++i) {
		EXPECT_EQ(list[i], result[i]);
		EXPECT_EQ(result[i], initArray[i]);
	}

	result[3] = 9;

	EXPECT_EQ(list[3], 4);
}

TEST(DequeTest, multiplicationMany)
{
	int initArray[5] = {1, 2, 3, 4, 5};
	int resultArray[25] = {1, 2, 3, 4, 5,
						   1, 2, 3, 4, 5,
						   1, 2, 3, 4, 5,
						   1, 2, 3, 4, 5,
						   1, 2, 3, 4, 5
						   };
	Deque<int> list{initArray, 5};
	Deque<int> result = list * 5;

	EXPECT_EQ(list.size(), 5);
	EXPECT_EQ(result.size(), 25);

	for (size_t i = 0; i < 5; ++i) 
		EXPECT_EQ(list[i], initArray[i]);

	for (size_t i = 0; i < 25; ++i) 
		EXPECT_EQ(result[i], resultArray[i]);
	

	result[3] = 9;

	EXPECT_EQ(list[3], 4);
}

TEST(DequeTest, asArrayEmpty)
{
	Deque<int> list;

	// This is an empty array, which is permissable because it was dynamically
	// allocated.  However, dereferencing this array is undefined behavior.  As
	// the First Ammendment to the C++ Standard states:
	//     "The committee shall make no rule that prevents C++ programmers from 
	//      shooting themselves in the foot."
	int* myArray = list.asArray();

	// We're simply asserting that there is a memory address.  Hooray!
	assert(myArray != nullptr);

	delete [] myArray;
}

TEST(DequeTest, asArrayOne)
{
	Deque<int> list;
	list.append(1);

	int* myArray = list.asArray();

	EXPECT_EQ(myArray[0], 1);
	list[0] = 9;
	EXPECT_EQ(myArray[0], 1);
	myArray[0] = 17;
	EXPECT_EQ(list[0], 9);

	delete [] myArray;
}

TEST(DequeTest, asArrayMany)
{
	int initArray[5] = {1, 2, 3, 4, 5};
	Deque<int> list{initArray, 5};

	int* myArray = list.asArray();

	for (size_t i = 0; i < 5; ++i)
		EXPECT_EQ(initArray[i], myArray[i]);

	list[0] = 9;
	EXPECT_EQ(myArray[0], 1);
	myArray[0] = 17;
	EXPECT_EQ(list[0], 9);

	delete [] myArray;
}
