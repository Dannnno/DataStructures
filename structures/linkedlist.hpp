/**
 * \file linkedlist.hpp
 * \author Dan Obermiller
 * \brief Implementation of a singly-linked list.
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP 1

#include <cstddef>
#include <iterator>

#include "list.hpp"
#include "../exceptions.hpp"


/**
 * \brief A paramaterized singly-linked list
 */
template <typename T>
class LinkedList : public List<T>
{
private:
	/**
	 * \brief Iterator for a linkedlist.
	 */
	class Iterator;

	/**
	 * \brief Constant iterator for a linkedlist.
	 */
	class ConstIterator;

	/**
	 * \brief Node of a linkedlist
	 */
	struct ListNode;
public:

	/**
	 * \brief A default constructor for a linked list.
	 */
	LinkedList();

	/**
	 * \brief A constructor from an array.
	 */
	LinkedList(T* arr, std::size_t length);

	/**
	 * \brief Copy constructor.
	 */
	LinkedList(const LinkedList<T>& orig);

	/**
	 * \brief Move constructor.
	 */
	LinkedList(LinkedList<T>&& other);

    /**
	 * \brief Assignment to a list;
	 */
	LinkedList<T>& operator=(LinkedList<T> rhs);

	/**
	 * \brief The destructor for a linked list.
	 */
	~LinkedList();

	/**
	 * \brief Non-member function version of swap.
	 */
	template <class P>
	friend void swap(LinkedList<P>& lhs, LinkedList<P>& rhs);

	/**
	 * \brief The head (first item) of the list.
	 */
	T& getHead();

	/**
	 * \brief Constant version of getHead()
	 */
	const T& getHead() const;

	/**
	 * \brief The tail (last item) of the list.
	 */
	T& getTail();

	/**
	 * \brief Constant version of getTail()
	 */
	const T& getTail() const;

	/**
  	 * \brief Returns the size of the list
  	 */
  	std::size_t size() const;

  	/**
  	 * \brief Returns whether or not the list is empty.
  	 */
	bool isEmpty() const;

	/**
	 * \brief Adds a node to the end of the list.
	 * \post All nodes have the appropriate "next_" and the list has
	 *		 the appropriate size.
	 */
	void append(T value);

	/**
	 * \brief Removes the first item in the list.
	 */
	void remove();

	/**
	 * \brief Removes the nth item in the list.
	 */
	void remove(std::size_t n);

	/**
	 * \brief Removes and returns a copy of the value of the first item 
	 *        in the list.
	 */
	T pop();

	/**
	 * \brief Removes and returns a copy of the value of the nth item 
	 *		  in the list.
	 */
	T pop(std::size_t n);

	/**
	 * \brief inserts an item at the indicated index.
	 */
	void insert(std::size_t index, T value);

	/**
	 * \brief Overloads the addition operator.
	 * \details Adds two lists together and returns the result.
	 */
    template <typename P>
    friend LinkedList<P> operator+(LinkedList<P> lhs, LinkedList<P> rhs);

	/**
	 * \brief Overloads the multiplication operator.
	 * \details Allows us to make the list repeat n times.
	 */
	template <typename P>
	friend LinkedList<P> operator*(LinkedList<P> lhs, std::size_t n);

	/**
	 * \brief Overloads the mutable subscript operator.
	 */
    T& operator[](std::size_t index);

    /**
     * \brief Overloads the immutable subscript operator.
     */
  	const T& operator[](std::size_t index) const;

  	/**
  	 * \brief Overloads the equivalence operator.
  	 */
  	bool operator==(const LinkedList<T>& rhs) const;

  	/**
  	 * \brief Overloads the inequivalence operator.
  	 */
  	bool operator!=(const LinkedList<T>& rhs) const;

  	/**
  	 * \brief Returns an array of the values within the list.
  	 * \details This is a dynamically allocated array and needs to be
  	 *          explicitly deleted.
  	 */
  	T* asArray() const;

	/**
	 * \brief Overloads the << operator.
	 */
	template <class P>
	friend std::ostream& operator<<(
		std::ostream& str, const LinkedList<P>& list);

  	typedef Iterator iterator;
  	typedef ConstIterator const_iterator;

    /**
     * \brief Returns the start of the ListIterator.
     */
	iterator begin();

	/**
	 * \brief Returns the end of the ListIterator.
	 */
    iterator end();

    /** 
     * \brief Returns a costant version of the ListIterator (from the start)
     */
    const_iterator begin() const;

    /**
     * \brief Returns a constant version of the ListIterator (at the end).
     */
    const_iterator end() const;

    /**
     * \brief Sorts the current list.
     */
    void sort();

    /**
     * \brief Returns a copy of the list in sorted order.
     * \post The original list is unchanged.
     */
    LinkedList<T> sorted() const;

    /**
     * \brief Reverses the order of the list.
     */
    void reverse();

    /**
     * \brief Returns a copy of the list, reversed.
     * \post The original list is unchanged.
     */
    LinkedList<T> reversed() const;

    /**
     * \brief Returns an array of the items in the list.
     */
    T* toArray() const;

private:
	class Iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
	    /**
		 * \brief Prefix increment operator overloading.
		 */
		Iterator& operator++();

		/**
		 * \brief Postfix increment operator overloading.
		 */
		Iterator operator++(int) const;

		/**
		 * \brief Dereferencing operator overloading.
		 */
		const T& operator*() const;

		/**
		 * \brief Member access operator overriding.
		 */
		const T* operator->() const;

		/**
		 * \brief Equality operator overriding.
		 */
		bool operator==(const Iterator& rhs) const;

		/**
		 * \brief Inequality operator overriding.
		 */
		bool operator!=(const Iterator& rhs) const;

	private:
		friend class LinkedList;
		/**
	     * \brief The default constructor.
	     */
	    Iterator() = delete;
	    /**
	     * \brief All iterators should have a current node.
	     */
	    Iterator(ListNode* node) : current_{node}
	    {
	    }
		
		ListNode* current_;
	};

	class ConstIterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
	    /**
		 * \brief Prefix increment operator overloading.
		 */
		ConstIterator& operator++();

		/**
		 * \brief Postfix increment operator overloading.
		 */
		ConstIterator operator++(int) const;

		/**
		 * \brief Dereferencing operator overloading.
		 */
		const T& operator*() const;

		/**
		 * \brief Member access operator overriding.
		 */
		const T* operator->() const;

		/**
		 * \brief Equality operator overriding.
		 */
		bool operator==(const ConstIterator& rhs) const;

		/**
		 * \brief Inequality operator overriding.
		 */
		bool operator!=(const ConstIterator& rhs) const;

	private:
		friend class LinkedList;
		/**
	     * \brief The default constructor.
	     */
	    ConstIterator() = delete;
	    /**
	     * \brief All iterators should have a current node.
	     */
	    ConstIterator(ListNode* node) : current_{node}
	    {
	    }
		
		ListNode* current_;
	};

	/**
	 * \brief Node of a linkedlist
	 */
	struct ListNode
	{
		T value_;
		ListNode* next_;
	};

	/**
	 * \brief Gets a list node at the given index
	 */
	ListNode* getListNode(std::size_t index) const
	{
		if (index >= numElements_)
			throw IndexOutOfBoundsException(index, "LinkedList");

		std::size_t i = 0;
		ListNode* current = head_;

		while (i < index) {
			current = current->next_;
			++i;
		}
		return current;
	}

	std::size_t numElements_;
	ListNode* head_;
	ListNode* tail_;
};

#include "_linkedlist.hpp"

#endif
