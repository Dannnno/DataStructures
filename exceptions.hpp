/**
 * \file exceptions.hpp
 * \author Dan Obermiller
 * \brief Exceptions used in various data structures
 */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP 1

#include <exception>
#include <cstddef>
#include <string>

/**
 * \brief My own implementation of to_string.  Necessary because MinGW
 * 		  has some weird problems with it.
 */
template <typename T> std::string toString(T value);

/**
 * \brief Exception to be thrown if an illegal index would be accessed
 *        by a program.
 */
class IndexOutOfBoundsException: public std::exception
{
public:
	/**
	 * \brief Default constructor.
	 */
	IndexOutOfBoundsException();

	/**
	 * \brief Constructor for the exception.
	 */
	IndexOutOfBoundsException(std::size_t index, std::string type);

	/**
	 * \brief Destroys the dynamically allocated message array.
	 */
	~IndexOutOfBoundsException();

	/**
	 * \brief Throws the message for the exception.
	 */
 	virtual const char* what() const throw();

private:
	char* message_;
	std::size_t index_;
	std::string iterableType_;
};

#endif
