#include <sstream>
#include <string>
#include <cstddef>

#include "gtest/gtest.h"

#include "../algorithms/mergesort.hpp"
#include "../structures/linkedlist.hpp"


using std::size_t;

TEST(MergeSortTest, testOneItemArrayInPlace)
{
	int array[1] = {1};
	int sorted[1] = {1};
	mergesort(array, 1);

	for (size_t i = 0; i < 1; ++i)
		EXPECT_EQ(array[i], sorted[i]);
}

TEST(MergeSortTest, testManyItemArrayInPlace)
{
	int array[5] = {3, 5, 2, 1, 4};
	int sorted[5] = {1, 2, 3, 4, 5};
	mergesort(array, 5);

	for (size_t i = 0; i < 5; ++i)
		EXPECT_EQ(array[i], sorted[i]);
}

TEST(MergeSortTest, testOneItemArrayCopy)
{
	int array[1] = {1};
	int sorted[1] = {1};
	int newArray[1];
	mergesort(array, 1, newArray);

	for (size_t i = 0; i < 1; ++i)
		EXPECT_EQ(newArray[i], sorted[i]);
}

TEST(MergeSortTest, testManyItemArrayCopy)
{
	int array[5] = {3, 5, 2, 1, 4};
	int sorted[5] = {1, 2, 3, 4, 5};
	int newArray[5];
	mergesort(array, 5, newArray);

	for (size_t i = 0; i < 1; ++i) {
		EXPECT_EQ(newArray[i], sorted[i]);
		EXPECT_NE(newArray[i], array[i]);
	}
}

TEST(MergeSortTest, testEmptyListInPlace)
{

}

TEST(MergeSortTest, testOneItemListInPlace)
{

}

TEST(MergeSortTest, testManyItemListInPlace)
{

}

TEST(MergeSortTest, testEmptyListCopy)
{

}

TEST(MergeSortTest, testOneItemListCopy)
{

}

TEST(MergeSortTest, testManyItemListCopy)
{

}
