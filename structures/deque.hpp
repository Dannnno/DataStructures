/**
 * \file deque.hpp
 * \author Dan Obermiller
 * \brief Implementation of a doubly linked list.
 */

#ifndef DEQUE_HPP
#define DEQUE_HPP 1


#include <cstddef>
#include <iterator>

#include "list.hpp"
#include "../exceptions.hpp"


/**
 * \brief A paramaterized doubly-linked list
 */
template <typename T>
class Deque : public List<T>
{
private:
	/**
	 * \brief Iterator for a deque.
	 */
	class Iterator;

	/**
	 * \brief Constant iterator for a deque.
	 */
	class ConstIterator;

	/**
	 * \brief Reverse iterator for a deque.
	 */
	class ReverseIterator;

	/**
	 * \brief Constant reverse iterator for a deque.
	 */
	class ConstReverseIterator;

	/**
	 * \brief Node of a deque
	 */
	struct ListNode;
public:

	/**
	 * \brief A default constructor for a deque.
	 */
	Deque();

	/**
	 * \brief A constructor from an array.
	 */
	Deque(T* arr, std::size_t length);

	/**
	 * \brief Copy constructor.
	 */
	Deque(const Deque<T>& orig);

	/**
	 * \brief Move constructor.
	 */
	Deque(Deque<T>&& other);

    /**
	 * \brief Assignment to a list;
	 */
	Deque<T>& operator=(Deque<T> rhs);

	/**
	 * \brief The destructor for a deque.
	 */
	~Deque();

	/**
	 * \brief Non-member function version of swap.
	 */
	template <class P>
	friend void swap(Deque<P>& lhs, Deque<P>& rhs);

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
	 * \brief Adds a node to the front of the list.
	 */
	void appendLeft(T value);

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
	 * \brief Determines the index of an element.
	 */
	std::size_t index_of(T const& value) const;

	/**
	 * \brief Determines whether or not the value is present.
	 */
	bool contains(T const& value) const;

	/**
	 * \brief Overloads the addition operator.
	 * \details Adds two lists together and returns the result.
	 */
    template <typename P>
    friend Deque<P> operator+(Deque<P> lhs, Deque<P> rhs);

	/**
	 * \brief Overloads the multiplication operator.
	 * \details Allows us to make the list repeat n times.
	 */
	template <typename P>
	friend Deque<P> operator*(Deque<P> lhs, std::size_t n);

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
  	bool operator==(const Deque<T>& rhs) const;

  	/**
  	 * \brief Overloads the inequivalence operator.
  	 */
  	bool operator!=(const Deque<T>& rhs) const;

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
		std::ostream& str, const Deque<P>& list);

  	typedef Iterator iterator;
  	typedef ConstIterator const_iterator;
  	typedef ReverseIterator reverse_iterator;
  	typedef ConstReverseIterator const_reverse_iterator;

    /**
     * \brief Start of the deque.
     */
	iterator begin();

	/**
	 * \brief Termination of the deque.
	 */
    iterator end();

    /** 
     * \brief Start of the deque.
     */
    const_iterator begin() const;

    /**
     * \brief Termination of the deque.
     */
    const_iterator end() const;

    /**
     * \brief End of the deque.
     */
	reverse_iterator rbegin();

	/**
	 * \brief Termination of the reversed deque.
	 */
    reverse_iterator rend();

    /** 
     * \brief End of the deque.
     */
    const_reverse_iterator rbegin() const;

    /**
     * \brief Terminatin of the reversed deque.
     */
    const_reverse_iterator rend() const;

    /**
     * \brief Sorts the current list.
     */
    void sort();

    /**
     * \brief Returns a copy of the list in sorted order.
     * \post The original list is unchanged.
     */
    Deque<T> sorted() const;

    /**
     * \brief Reverses the order of the list.
     */
    void reverse();

    /**
     * \brief Returns a copy of the list, reversed.
     * \post The original list is unchanged.
     */
    Deque<T> reversed() const;

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
		friend class Deque;
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
		friend class Deque;
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

	class ReverseIterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
	    /**
		 * \brief Prefix increment operator overloading.
		 */
		ReverseIterator& operator++();

		/**
		 * \brief Postfix increment operator overloading.
		 */
		ReverseIterator operator++(int) const;

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
		bool operator==(const ReverseIterator& rhs) const;

		/**
		 * \brief Inequality operator overriding.
		 */
		bool operator!=(const ReverseIterator& rhs) const;

	private:
		friend class Deque;
		/**
	     * \brief The default constructor.
	     */
	    ReverseIterator() = delete;
	    /**
	     * \brief All iterators should have a current node.
	     */
	    ReverseIterator(ListNode* node) : current_{node}
	    {
	    }
		
		ListNode* current_;
	};

	class ConstReverseIterator : 
		public std::iterator<std::forward_iterator_tag, T>
	{
	public:
	    /**
		 * \brief Prefix increment operator overloading.
		 */
		ConstReverseIterator& operator++();

		/**
		 * \brief Postfix increment operator overloading.
		 */
		ConstReverseIterator operator++(int) const;

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
		bool operator==(const ConstReverseIterator& rhs) const;

		/**
		 * \brief Inequality operator overriding.
		 */
		bool operator!=(const ConstReverseIterator& rhs) const;

	private:
		friend class Deque;
		/**
	     * \brief The default constructor.
	     */
	    ConstReverseIterator() = delete;
	    /**
	     * \brief All iterators should have a current node.
	     */
	    ConstReverseIterator(ListNode* node) : current_{node}
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
		ListNode* previous_;
	};

	/**
	 * \brief Gets a list node at the given index
	 */
	ListNode* getListNode(std::size_t index) const;

	std::size_t numElements_;
	ListNode* head_;
	ListNode* tail_;
};

#include "_deque.hpp"

#endif
