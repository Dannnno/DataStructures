/**
 * \file _nonhashmap.hpp
 * \brief Private implementation file of the nonhashing mapping type.
 */

#ifndef _NONHASH_MAP_HPP
#define _NONHASH_MAP_HPP 1

#include <utility>
#include <cstddef>

#include "map.hpp"
#include "deque.hpp"
#include "../exceptions.hpp"


template <typename K, typename V> inline
NonHashMap<K, V>::NonHashMap() {}

template <typename K, typename V> inline
NonHashMap<K, V>::NonHashMap(NonHashMap<K, V> const& orig) 
{
	Deque<NonHashMap<K, V>::Key> tmp{orig.keys_};
	keys_ = tmp;
}

template <typename K, typename V> inline
NonHashMap<K, V>::NonHashMap(NonHashMap<K, V>&& other) 
{
	#include <iostream>

	std::cout << "Move constructor" << std::endl;
	swap(*this, other);
}

template <typename K, typename V> inline
NonHashMap<K, V>& NonHashMap<K, V>::operator=(NonHashMap<K, V> rhs) 
{
	swap(*this, rhs);
	return *this;
}

template <typename K, typename V> inline
void swap(NonHashMap<K, V>& lhs, NonHashMap<K, V>& rhs) 
{
	swap(lhs.keys_, rhs.keys_);
}

template <typename K, typename V> inline
void NonHashMap<K, V>::addValue(K key, V value) 
{
	if (!contains(key))
	 	keys_.append(Key{key, value});
	 else
	 	throw KeyError<K>{key, "NonHashMap"};
}

template <typename K, typename V> inline
void NonHashMap<K, V>::removeValue(K) {}

template <typename K, typename V> inline
V& NonHashMap<K, V>::getValue(K) const
{
	V* a = new V;
	return *a;
}

template <typename K, typename V> inline
std::size_t NonHashMap<K, V>::size() const
{
	return keys_.size();
}

template <typename K, typename V> inline
bool NonHashMap<K, V>::isEmpty() const
{
	return keys_.isEmpty(); 
}

template <typename K, typename V> inline
Deque<K>* NonHashMap<K, V>::getKeys() const
{
	return new Deque<K>;
}

template <typename K, typename V> inline
Deque<V>* NonHashMap<K, V>::getValues() const
{
	return new Deque<V>;
}

template <typename K, typename V> inline
bool NonHashMap<K, V>::contains(K key) const
{
	return keys_.contains(Key{key, V()});
}

template <typename K, typename V> inline
bool NonHashMap<K, V>::Key::operator==(Key const& k) const
{
	return key_ == k.key_;
}

#endif
