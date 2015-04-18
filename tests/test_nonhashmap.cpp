#include <cassert>
#include <sstream>
#include <string>
#include <utility>

#include "gtest/gtest.h"

#include "../structures/nonhashmap.hpp"
#include "../exceptions.hpp"


TEST(NonHashMapTest, constructor)
{
	NonHashMap<int, std::string> map;
	EXPECT_EQ(0, map.size());
	assert(map.isEmpty());
}

TEST(NonHashMapTest, copyConstructor)
{
	NonHashMap<int, std::string> map;
	map.addValue(5, "hello");
	NonHashMap<int, std::string> copy{map};

	EXPECT_EQ(copy.size(), map.size());
	map.addValue(6, "hi");
	EXPECT_NE(copy.size(), map.size());
}

TEST(NonHashMapTest, DISABLED_moveConstructor)
{
	NonHashMap<int, std::string> map;
	map.addValue(5, "hello");
	assert(map.size() == 1);
	NonHashMap<int, std::string> copy{std::move(map)};
	assert(copy.size() == 1);

	EXPECT_EQ(copy.size(), map.size());
	map.addValue(6, "hi");
	std::cout << map.size() << std::endl;
	EXPECT_NE(copy.size(), map.size());
}

TEST(NonHashMapTest, swap)
{
	NonHashMap<int, std::string> map1;
	map1.addValue(5, "hello");
	NonHashMap<int, std::string> map2;
	map2.addValue(6, "hi");
	map2.addValue(7, "bye");

	swap(map1, map2);
	EXPECT_EQ(map1.size(), 2);
	EXPECT_EQ(map2.size(), 1);
}

TEST(NonHashMapTest, assignment)
{
	NonHashMap<int, std::string> map;
	map.addValue(5, "hello");
	NonHashMap<int, std::string> result = map;

	EXPECT_EQ(result.size(), map.size());
	map.addValue(6, "hi");
	EXPECT_NE(result.size(), map.size());
}

TEST(NonHashMapTest, addValueNotPresent)
{
	NonHashMap<int, std::string> map;
	map.addValue(5, "hello");
	EXPECT_EQ(true, !map.isEmpty());
	EXPECT_EQ(1, map.size());
}

TEST(NonHashMapTest, addValuePresent)
{
	NonHashMap<int, std::string> map;
	map.addValue(5, "hello");
	EXPECT_THROW(map.addValue(5, "goodbye"), KeyError<int>);
}

TEST(NonHashMapTest, containsPresent)
{
	NonHashMap<int, std::string> map;
	map.addValue(5, "hello");
	EXPECT_EQ(true, map.contains(5));
}

TEST(NonHashMapTest, containsNotPresent)
{
	NonHashMap<int, std::string> map;
	map.addValue(6, "hello");
	EXPECT_EQ(false, map.contains(5));
}
