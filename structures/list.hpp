/**
 * \file list.hpp
 * \author Dan Obermiller
 * \brief Abstract base class of list types.
 */

#ifndef LIST_HPP
#define LIST_HPP 1

#include <cstddef>
#include <string>
#include <iostream>
#include <iterator>

#include "listnode.hpp"
#include "listiterator.hpp"
#include "../exceptions.hpp"


/**
 * \brief A paramaterized doubly linked list
 */
template <typename T>
class List;


/**
 * \brief Overloading the << operator to allow clean string 
 *        representations of the list.
 */
template <typename T>
std::ostream& operator<<(std::ostream& str, const List<T>& list);


template <typename T>
class List
{
public:
	/**
	 * \brief The destructor.
	 */
	virtual ~List() {}

	/**
	 * \brief The head (first item) of the list.
	 */
	virtual T& getHead() = 0;

	/**
	 * \brief Constant version of getHead()
	 */
	virtual const T& getHead() const = 0;

	/**
	 * \brief The tail (last item) of the list.
	 */
	virtual T& getTail() = 0;

	/**
	 * \brief Constant version of getTail()
	 */
	virtual const T& getTail() const = 0;

	/**
	 * \brief Adds a node to the end of the list.
	 * \post All nodes have the appropriate "next_" and the list has
	 *		 the appropriate size.
	 */
	virtual void append(T value) = 0;

	/**
	 * \brief Removes the first item in the list.
	 */
	virtual void remove() = 0;

	/**
	 * \brief Removes the nth item in the list.
	 */
	virtual void remove(std::size_t n) = 0;

	/**
	 * \brief Removes and returns a copy of the value of the first item 
	 *        in the list.
	 */
	virtual T pop() = 0;

	/**
	 * \brief Removes and returns a copy of the value of the nth item 
	 *		  in the list.
	 */
	virtual T pop(std::size_t n) = 0;

	/**
	 * \brief inserts an item at the indicated index.
	 */
	virtual void insert(std::size_t index, T value) = 0;

	/**
	 * \brief Overloads the mutable subscript operator.
	 */
    virtual T& operator[](std::size_t index) = 0;

    /**
     * \brief Overloads the immutable subscript operator.
     */
  	virtual const T& operator[](std::size_t index) const = 0;

  	/**
  	 * \brief Returns the size of the list
  	 */
  	virtual std::size_t size() const = 0;

  	/**
  	 * \brief Returns whether or not the list is empty.
  	 */
	virtual bool isEmpty() const = 0;

    /**
     * \brief Returns the start of the iterator.
     */
	virtual ListIterator<T> begin() = 0;

	/**
	 * \brief Returns the end of the iterator.
	 */
    virtual ListIterator<T> end() = 0;

    /** 
     * \brief Returns a constant version of the iterator (from the start)
     */
    virtual ConstListIterator<T> begin() const = 0;

    /**
     * \brief Returns a constant version of the iterator (at the end).
     */
    virtual ConstListIterator<T> end() const = 0;

    /**
     * \brief Sorts the current list.
     */
    virtual void sort() = 0;

    /**
     * \brief Returns a copy of the list in sorted order.
     * \post The original list is unchanged.
     */
    // virtual List<T> sorted() const = 0;

    /**
     * \brief Reverses the order of the list.
     */
    virtual void reverse() = 0;

    /**
     * \brief Returns a copy of the list, reversed.
     * \post The original list is unchanged.
     */
    // virtual List<T> reversed() const = 0;

private:
	std::size_t numElements_;
	ListNode<T>* head_;
	ListNode<T>* tail_;
};

template <typename T> inline 
std::ostream& operator<<(std::ostream& str, const List<T>& list)
{
	str << "{";
	for (auto node : list) {
		str << node;
		if (node.getValue() != list.getTail())
			str << ", ";
	}
	str << "}" << std::endl;
	return str;
}

#endif
