/**
 * \file _exceptions.hpp
 * \author Dan Obermiller
 * \brief Private implementation file for my custom exceptions.
 */

#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP 1

#include <cstddef>
#include <exception>
#include <string>
#include <sstream>


template <typename T> inline
std::string toString(T value)
{
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

inline IndexOutOfBoundsException::IndexOutOfBoundsException()
{	
	message_ = new char[21];
	std::string mstring = "Index out of bounds.";
	for (std::size_t i = 0; i < 21; ++i) {
		message_[i] = mstring[i];
	}
}

inline IndexOutOfBoundsException::IndexOutOfBoundsException(
	std::size_t index, std::string type) : 
		index_(index), iterableType_(type) {	

	std::string indexString = toString<std::size_t>(index_);
	std::size_t arraySize = \
		46 + indexString.length() + iterableType_.length();
	message_ = new char[arraySize];

	std::string mstring = "Index " + indexString + " in iterable of type " + \
		iterableType_ + " is out of bounds.";
	for (std::size_t i = 0; i < arraySize; ++i) {
		message_[i] = mstring[i];
	}
}

inline IndexOutOfBoundsException::~IndexOutOfBoundsException()
{
	delete [] message_;
}

inline const char* IndexOutOfBoundsException::what() const throw()
{
	return message_;
}

template <typename KEY> inline
KeyError<KEY>::KeyError()
{
	message_ = new char[12];
	std::string mstring = "Invalid key";
	for (std::size_t i = 0; i < 12; ++i) {
		message_[i] = mstring[i];
	}
}

template <typename KEY> inline
KeyError<KEY>::KeyError(KEY key, std::string type) : 
	key_(key), mappingType_(type) {

	std::string keyString = toString<KEY>(key);
	std::size_t arraySize = \
		34 + keyString.length() + mappingType_.length();
	message_ = new char[arraySize];

	std::string mstring = "Key " + keyString + " is invalid for " + \
		"mapping type " + mappingType_;
	for (std::size_t i = 0; i < arraySize; ++i) {
		message_[i] = mstring[i];
	}
}

template <typename KEY> inline
KeyError<KEY>::~KeyError()
{
	delete [] message_;
}

template <typename KEY> inline	
const char* KeyError<KEY>::what() const throw()
{
	return message_;
}

#endif
