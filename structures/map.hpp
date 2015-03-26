/**
 * \file map.hpp
 * \brief Abstract base class for mapping types
 */

#ifndef MAP_HPP
#define MAP_HPP 1

#include <iterator>
#include <cstddef>

#include "deque.hpp"


/**
 * \brief Abstract base mapping class
 */
template <typename K, typename V>
class Map
{
public:
	/**
	 * \brief Virtual destructor.
	 */
	virtual ~Map() {}

	/**
	 * \brief Purely virtual function to add a value.
	 */
	virtual void addValue(K key, V value) = 0;

	/**
	 * \brief Purely virtual function to remove a value.
	 */
	virtual void removeValue(K key) = 0;

	/**
	 * \brief Purely virtual function to get a value.
	 */
	virtual V& getValue(K key) const = 0;

	/**
	 * \brief Purely virtual function to get the number of pairs in the map.
	 */
	virtual std::size_t size() const = 0;

	/**
	 * \brief Purely virtual function to determine if the map is empty.
	 */
	virtual bool isEmpty() const = 0;

	/**
	 * \brief Purely virtual function to retrieve a list of all keys in the map.
	 */
	virtual Deque<K>* getKeys() const = 0;

	/**
	 * \brief Purely virtual function to retrieve a list of all of the values in
	 *        the map.
	 */
	virtual Deque<V>* getValues() const = 0;
};

#endif
