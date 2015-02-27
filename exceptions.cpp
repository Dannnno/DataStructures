/**
 * \file exceptions.cpp
 * \author Dan Obermiller
 * \brief Exceptions used in various data structures
 */

#include <exception>
#include <cstddef>
#include <string>
#include <sstream>

#include "exceptions.hpp"

using std::string;
using std::size_t;
using std::ostringstream;


template <typename T> string toString(T value)
{
	ostringstream ss;
	ss << value;
	return ss.str();
}

IndexOutOfBoundsException::IndexOutOfBoundsException()
{	
	message_ = new char[21];
	string mstring = "Index out of bounds.";
	for (size_t i = 0; i < 21; ++i) {
		message_[i] = mstring[i];
	}
}

IndexOutOfBoundsException::IndexOutOfBoundsException(
	size_t index, string type) : 
		index_(index), iterableType_(type) {	

	string indexString = toString<size_t>(index_);
	size_t arraySize = \
		46 + indexString.length() + iterableType_.length();
	message_ = new char[arraySize];

	string mstring = "Index " + indexString + " in iterable of type " + \
		iterableType_ + " is out of bounds.";
	for (size_t i = 0; i < arraySize; ++i) {
		message_[i] = mstring[i];
	}
}

IndexOutOfBoundsException::~IndexOutOfBoundsException()
{
	delete [] message_;
}

const char* IndexOutOfBoundsException::what() const throw()
{
	return message_;
}

template <typename KEY>
KeyError<KEY>::KeyError()
{
	message_ = new char[12];
	string mstring = "Invalid key";
	for (size_t i = 0; i < 12; ++i) {
		message_[i] = mstring[i];
	}
}

template <typename KEY>
KeyError<KEY>::KeyError(KEY key, string type) : 
	key_(key), mappingType_(type) {

	string keyString = toString<KEY>(key);
	size_t arraySize = \
		34 + keyString.length() + mappingType_.length();
	message_ = new char[arraySize];

	string mstring = "Key " + keyString + " is invalid for " + \
		"mapping type " + mappingType_;
	for (size_t i = 0; i < arraySize; ++i) {
		message_[i] = mstring[i];
	}
}

template <typename KEY>
KeyError<KEY>::~KeyError()
{
	delete [] message_;
}

template <typename KEY>
const char* KeyError<KEY>::what() const throw()
{
	return message_;
}
