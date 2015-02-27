/**
 * \file listiterator.hpp
 * \brief Base implementation of list iterators.
 */

#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP 1

#include <iterator>

/**
 * \brief Underlying iterator class.
 */
template <typename T>
class ListIterator
{
public:
    
    typedef std::forward_iterator_tag iterator_category;
	
	/**
	 * \brief Prefix increment operator overloading.
	 */
	virtual ListIterator<T> operator++() = 0;

	/**
	 * \brief Postfix increment operator overloading.
	 */
	virtual ListIterator<T> operator++(int junk) = 0;

	/**
	 * \brief Dereferencing operator overloading.
	 */
	virtual T& operator*() = 0;

	/**
	 * \brief Member access operator overriding.
	 */
	virtual T* operator->() = 0;

	/**
	 * \brief Equality operator overriding.
	 */
	virtual bool operator==(const ListIterator<T>& rhs) = 0;

	/**
	 * \brief Inequality operator overriding.
	 */
	virtual bool operator!=(const ListIterator<T>& rhs) = 0;
};

/**
 * \brief Underlying ConstListIterator class.
 * \remarks Constant versions of everything provided in iterator.
 */
template <typename T>
class ConstListIterator
{
public:
    typedef std::forward_iterator_tag iterator_category;
    virtual ConstListIterator operator++() = 0;
    virtual ConstListIterator operator++(int junk) = 0;
    virtual const T& operator*() = 0;
    virtual const T* operator->() = 0;
    virtual bool operator==(const ConstListIterator<T>& rhs) = 0;
    virtual bool operator!=(const ConstListIterator<T>& rhs) = 0;
};

#endif
