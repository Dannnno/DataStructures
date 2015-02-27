/**
 * \file map.hpp
 * \author Dan Obermiller
 * \brief Implementation of a unidirectional mapping structure.
 * \remarks This map doesn't use hashing for the keys (or values).
 */

#ifndef MAP_HPP
#define MAP_HPP 1

#include <cstddef>

#include "deque.hpp"
#include "exceptions.hpp"


/**
 * \brief Non-hashing mapping type.
 */
template <typename KEY, typename VALUE>
class Map
{
public:

	/**
	 * \brief Default constructor.
	 */
	Map();

	/**
	 * \brief Returns a list of the keys.
	 */
	Deque<KEY> keys();

	/**
	 * \brief Returns a list of the values.
	 */
	Deque<VALUE> values();

	/**
	 * \brief Returns whether the map is empty.
	 */
	bool isEmpty();

	/**
	 * \brief Returns the number of pairs.
	 */
	std::size_t size();

	/**
	 * \brief Adds a key-value pair to the map, assuming the key does
	 *        not exist.
	 */
	void add(KEY k, VALUE v);

	/**
	 * \brief Removes a key-value pair from the map.
	 */
	void remove(KEY k);

	/**
	 * \brief Removes and returns a value based on its key
	 */
	VALUE* pop(KEY k);

	/**
	 * \brief Updates the value of a key.
	 */
	void update(KEY k, VALUE v);

	/**
	 * \brief Determines whether the key is in the mapping.
	 */
	bool contains(KEY k);

	/**
	 * \brief Overrides the subscript operator for easy access by key.
	 */
	VALUE& operator[](KEY key);

	/**
	 * \brief const version of the same.
	 */
	const VALUE& operator[](KEY key) const;

private:
	/** 
	 * \brief A key-value pair
	 */
	template <typename K, typename V> static struct KVPair {
		K* key_;
		V* value_;
	};
	Deque<KVPair<KEY, VALUE>> pairs_;
	std::size_t numPairs_;
};



template <typename KEY, typename VALUE> inline 
Map<KEY, VALUE>::Map() : 
	pairs_(Deque<KVPair<KEY, VALUE>), numPairs_(0) {
}

template <typename KEY, typename VALUE> inline
Deque<KEY> Map<KEY, VALUE>::keys() 
{
	Deque<KEY> deq;
	for (KVPair<KEY, VALUE> pair : pairs_) {
		deq.append(pairs->key_);
	}
	return deq;
}

template <typename KEY, typename VALUE> inline
Deque<VALUE> Map<KEY, VALUE>::values() 
{
	Deque<VALUE> deq;
	for (KVPair<KEY, VALUE> pair : pairs_) {
		deq.append(pairs->value_);
	}
	return deq;
}

template <typename KEY, typename VALUE> inline
bool Map<KEY, VALUE>::isEmpty() 
{
	return numPairs_ == 0;
}

template <typename KEY, typename VALUE> inline
std::size_T Map<KEY, VALUE>::size() 
{
	return numPairs_;
}

template <typename KEY, typename VALUE> inline
void Map<KEY, VALUE>::add(KEY k, VALUE v)
{
	if (!contains(k)) {
		KVPair p;
		p.key_ = k;
		p.value_ = v;
		pairs_.append(p);
		++numPairs_;
	} else
		throw KeyError(k, std::string("Map"));
}

template <typename KEY, typename VALUE> inline
void Map<KEY, VALUE>::remove(KEY k)
{
	if (contains(k)) {
		for(size_t i = 0; i < pairs_.length; ++i) {
			if (*pairs_[i].key_ == k) {
				pairs_.remove(i);
				--numPairs_;
				break;
			}
		}
	} else
		throw KeyError(k, std::string("Map"));
}

template <typename KEY, typename VALUE> inline
VALUE* Map<KEY, VALUE>::pop(Key k)
{
	if (contains(k)) {
		for(size_t i = 0; i < pairs_.length; ++i) {
			if (*pairs_[i].key_ == k) {
				VALUE v = pairs_[i].value_;
				pairs_.remove(i);
				--numPairs_;
				return v;
			}
		}
	} else
		throw KeyError(k, std::string("Map"));
}

template <typename KEY, typename VALUE> inline
void Map<KEY, VALUE>::update(KEY k, VALUE v)
{
	if (contains(k)) {

	}
}
	/**
	 * \brief Removes and returns a key-value pair.
	 */
	KVPair<KEY, VALUE> pop(KEY k);

	/**
	 * \brief Updates the value of a key.
	 */
	void update(KEY k, VALUE v);

	/**
	 * \brief Overrides the subscript operator for easy access by key.
	 */
	VALUE& operator[](KEY key);

	/**
	 * \brief const version of the same.
	 */
	const VALUE& operator[](KEY key) const;


#endif
