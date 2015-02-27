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
	 * \brief A default constructor.
	 */
	virtual List() = 0;

	/**
	 * \brief A constructor from an array.
	 */
	virtual List(T* arr, std::size_t length) = 0;

	/**
	 * \brief The destructor.
	 */
	virtual ~List() {}

	/**
	 * \brief The head (first item) of the list.
	 */
	T& getHead();

	/**
	 * \brief The tail (last item) of the list.
	 */
	T& getTail();

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
  	std::size_t size() const;

  	/**
  	 * \brief Returns whether or not the list is empty.
  	 */
	bool isEmpty() const;

	/**
	 * \brief Underlying iterator class.
	 */
	class iterator
	{
	public:
        
        typedef std::forward_iterator_tag iterator_category;
		
		/**
		 * \brief Prefix increment operator overloading.
		 */
		virtual iterator operator++() = 0;

		/**
		 * \brief Postfix increment operator overloading.
		 */
		virtual iterator operator++(int junk) = 0;

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
		virtual bool operator==(const iterator& rhs) = 0;

		/**
		 * \brief Inequality operator overriding.
		 */
		virtual bool operator!=(const iterator& rhs) = 0;
    };

    /**
     * \brief Underlying const_iterator class.
     * \remarks Constant versions of everything provided in iterator.
     */
    class const_iterator
    {
    public:
        typedef std::forward_iterator_tag iterator_category;
        virtual const_iterator operator++() = 0;
        virtual const_iterator operator++(int junk) = 0;
        virtual const T& operator*() = 0;
        virtual const T* operator->() = 0;
        virtual bool operator==(const self_type& rhs) = 0;
        virtual bool operator!=(const self_type& rhs) = 0;
    };

    /**
     * \brief Returns the start of the iterator.
     */
	virtual iterator begin() = 0;

	/**
	 * \brief Returns the end of the iterator.
	 */
    virtual iterator end() = 0;

    /** 
     * \brief Returns a costant version of the iterator (from the start)
     */
    virtual const_iterator begin() const = 0;

    /**
     * \brief Returns a constant version of the iterator (at the end).
     */
    virtual const_iterator end() const = 0;

    /**
     * \brief Sorts the current list.
     */
    virtual void sort() = 0;

    /**
     * \brief Returns a copy of the list in sorted order.
     * \post The original list is unchanged.
     */
    virtual List<T> sorted() const = 0;

    /**
     * \brief Reverses the order of the list.
     */
    virtual void reverse() = 0;

    /**
     * \brief Returns a copy of the list, reversed.
     * \post The original list is unchanged.
     */
    virtual List<T> reversed() = 0;

private:
	std::size_t numElements_;
	ListNode<T>* head_;
	ListNode<T>* tail_;
};

template <typename T> inline T& List<T>::getHead()
{
	return head_->value_;
}

template <typename T> inline T& List<T>::getTail()
{
	return tail_->value_;
}

template <typename T> inline std::size_t List<T>::size() const
{
	return numElements_;
}

template <typename T> inline bool List<T>::isEmpty() const
{
	return numElements_ == 0;
}

template <typename T> inline 
std::ostream& operator<<(std::ostream& str, const List<T>& list)
{
	str << "{";
	for (ListNode<T>* node : list) {
		str << *node;
		if (i != list.size()-1) 
			str << ", ";
	}
	str << "}" << std::endl;
	return str;
}

#endif
