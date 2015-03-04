#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "../algorithms/mergesort.hpp"
#include "../structures/linkedlist.hpp"


TEST(MergeSortTest, testOneItemArrayInPlace)
{
	int array[1] = {1};
	int sorted[1] = {1};
	mergesort(array, 1);

	EXPECT_EQ(array, sorted);
}

TEST(MergeSortTest, testManyItemArrayInPlace)
{
	int array[5] = {3, 5, 2, 1, 4};
	int sorted[5] = {1, 2, 3, 4, 5};
	mergesort(array, 5);

	EXPECT_EQ(sorted, array);
}

TEST(MergeSortTest, testOneItemArrayCopy)
{
	int array[1] = {1};
	int sorted[1] = {1};
	int newArray[1];
	mergesort(array, 1, newArray);

	EXPECT_EQ(newArray, sorted);
}

TEST(MergeSortTest, testManyItemArrayCopy)
{
	int array[5] = {3, 5, 2, 1, 4};
	int sorted[5] = {1, 2, 3, 4, 5};
	int newArray[5];
	mergesort(array, 5, newArray);

	EXPECT_EQ(sorted, newArray);
	EXPECT_NE(newArray, array);
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
