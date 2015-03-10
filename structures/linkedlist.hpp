/**
 * \file linkedlist.hpp
 * \author Dan Obermiller
 * \brief Implementation of a singly-linked list.
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP 1

#include <cstddef>
#include <string>
#include <iostream>
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
	 * \brief The destructor for a linked list.
	 */
	~LinkedList();

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


template <typename T> inline LinkedList<T>::LinkedList() :
	numElements_{0}, head_{nullptr}, tail_{nullptr} {
}

template <typename T> inline LinkedList<T>::LinkedList(
	T* arr, std::size_t length) : 
		numElements_{length}, head_{new ListNode{arr[0], nullptr}} {

	ListNode* current{head_};
	ListNode* next = new ListNode{0, nullptr};

	for (std::size_t i = 1; i < length; ++i) {
		next = new ListNode{arr[i], nullptr};
		current->next_ = next;
		current = next;
	}
	tail_ = current;
}

template <typename T> inline LinkedList<T>::~LinkedList()
{
	ListNode* current = head_;
	ListNode* next = nullptr;

	for (std::size_t i = 0; i < numElements_; ++i) {
		next = current->next_;
		delete current;
		current = next;
	}
}

template <typename T> inline T& LinkedList<T>::getHead()
{
	if (head_ != nullptr)
		return head_->value_;
	else
		throw IndexOutOfBoundsException(0, "LinkedList");
}

template <typename T> inline T& LinkedList<T>::getTail()
{
	if (tail_ != nullptr)
		return tail_->value_;
	else
		throw IndexOutOfBoundsException(0, "LinkedList");
}

template <typename T> inline const T& LinkedList<T>::getHead() const
{
	if (head_ != nullptr)
		return head_->value_;
	else
		throw IndexOutOfBoundsException(0, "LinkedList");
}

template <typename T> inline const T& LinkedList<T>::getTail() const
{
	if (tail_ != nullptr)
		return tail_->value_;
	else
		throw IndexOutOfBoundsException(0, "LinkedList");
}

template <typename T> inline std::size_t LinkedList<T>::size() const
{
	return numElements_;
}

template <typename T> inline bool LinkedList<T>::isEmpty() const
{
	return numElements_ == 0;
}

template <typename T> inline 
void LinkedList<T>::append(T node)
{
	ListNode* newListNode = new ListNode{node, nullptr};
	if (numElements_ == 0) {
		head_ = newListNode;
		tail_ = head_;
	} else if (numElements_ == 1) {
		head_->next_ = newListNode;
		tail_ = newListNode;
	} else {
		ListNode* last = tail_;
		last->next_ = newListNode;
		tail_ = newListNode;
	}

	++numElements_;
}

template <typename T> inline
void LinkedList<T>::remove()
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, "LinkedList");

	// Setting it up like this eliminates duplicate code.
	ListNode* newHead = nullptr;
	if (numElements_ > 1) {
		newHead = head_->next_;
	}
	delete head_;
	head_ = newHead;
	--numElements_;
}

template <typename T> inline
void LinkedList<T>::remove(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, "LinkedList");

	std::size_t index = n-1;
	ListNode* prev = getListNode(index);
	ListNode* toRemove = prev->next_;
	ListNode* after = toRemove->next_;
	delete toRemove;
	prev->next_ = after;
	--numElements_;
}

template <typename T> inline
T LinkedList<T>::pop()
{
	// Setting it up like this eliminates duplicate code.
	ListNode* newHead = nullptr;
	T value;
	if (numElements_ > 1) {
		newHead = head_->next_;
		value = head_->value_;
	} else if (numElements_ == 1)
		value = head_->value_;
	else 
		throw IndexOutOfBoundsException(0, "LinkedList");
	
	delete head_;
	head_ = newHead;
	--numElements_;
	return value;
}

template <typename T> inline
T LinkedList<T>::pop(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, "LinkedList");

	std::size_t index = n-1;
	ListNode* prev = getListNode(index);
	ListNode* toRemove = prev->next_;
	ListNode* after = toRemove->next_;
	T value = toRemove->value_;
	delete toRemove;
	prev->next_ = after;
	--numElements_;	
	return value;
}

template <typename T> inline
void LinkedList<T>::insert(std::size_t n, T value)
{
	if (n > numElements_)
		throw IndexOutOfBoundsException(n, "LinkedList");

	ListNode* newListNode = new ListNode{value, nullptr};

	if (numElements_ == 0) {
		head_ = newListNode;
		tail_ = newListNode;
	} else if (numElements_ == n) {
		tail_->next_ = newListNode;
		tail_ = newListNode;
	} else if (n == 0) {
		newListNode->next_ = head_;
		head_ = newListNode;
	} else {
		std::size_t index = n - 1;
		ListNode* prev = getListNode(index);
		ListNode* toPush = prev->next_;
		
		prev->next_ = newListNode;
		newListNode->next_ = toPush;
	}
	++numElements_;
}

template <typename T> inline 
T& LinkedList<T>::operator[](std::size_t index)
{
	return getListNode(index)->value_;
}

template <typename T> inline 
const T& LinkedList<T>::operator[](std::size_t index) const
{
	return getListNode(index)->value_;
}

template <typename T> inline 
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	bool sizes = size() == rhs.size();

	if (!sizes)
		return false;

	ListNode* lh = head_;
	ListNode* rh = rhs.head_;

	for (std::size_t i = 0; i < numElements_; ++i) {
		if (lh->value_ != rh->value_)
			return false;
		lh = lh->next_;
		rh = rh->next_;
	}
	return true;
}

template <typename T> inline 
bool LinkedList<T>::operator!=(const LinkedList<T>& rhs) const
{
	return !(*this == rhs);
}

template <typename T> inline
typename LinkedList<T>::iterator LinkedList<T>::begin() 
{
	return iterator{head_};	
}

template <typename T> inline
typename LinkedList<T>::iterator LinkedList<T>::end()
{
	return Iterator{nullptr};
}

template <typename T> inline
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const 
{
	return ConstIterator{head_};
}

template <typename T> inline
typename LinkedList<T>::const_iterator LinkedList<T>::end() const
{
	return ConstIterator{nullptr};
}

template <typename T> inline
void LinkedList<T>::sort() // Uses a mergesort algorithm
{

}

template <typename T> inline
LinkedList<T> LinkedList<T>::sorted() const
{
	LinkedList<T> newList;
	return newList;
}

template <typename T> inline
void LinkedList<T>::reverse()
{

}

template <typename T> inline
LinkedList<T> LinkedList<T>::reversed() const
{
	LinkedList<T> newList;
	return newList;
}

template <typename T> inline
typename LinkedList<T>::iterator&
LinkedList<T>::iterator::operator++()
{
	current_ = current_->next_;
	return *this;
}

template <typename T> inline
typename LinkedList<T>::const_iterator& 
LinkedList<T>::const_iterator::operator++()
{
	current_ = current_->next_;
	return *this;
}

template <typename T> inline
typename LinkedList<T>::iterator
LinkedList<T>::iterator::operator++(int) const
{
    auto old = current_;
    current_ = current_->next_;
    return Iterator{old};
}

template <typename T> inline
typename LinkedList<T>::const_iterator
LinkedList<T>::const_iterator::operator++(int) const
{
    auto old = current_;
    current_ = current_->next_;
    return Iterator{old};
}

template <typename T> inline
const T& LinkedList<T>::iterator::operator*() const
{
	return current_->value_;
}

template <typename T> inline
const T& LinkedList<T>::const_iterator::operator*() const
{
	return current_->value_;
}

template <typename T> inline
const T* LinkedList<T>::iterator::operator->() const
{
	return current_->value_;
}

template <typename T> inline
const T* LinkedList<T>::const_iterator::operator->() const
{
	return current_->value_;
}

template <typename T> inline
bool LinkedList<T>::iterator::operator==(const iterator& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T> inline
bool LinkedList<T>::const_iterator::operator==(const const_iterator& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T> inline
bool LinkedList<T>::iterator::operator!=(const iterator& rhs) const
{
	return !(*this == rhs);
} 

template <typename T> inline
bool LinkedList<T>::const_iterator::operator!=(
	const const_iterator& rhs) const
{
	return !(*this == rhs);
} 

template <typename T> inline 
std::ostream& operator<<(std::ostream& str, const LinkedList<T>& list)
{
	str << "{";
	std::size_t i = 0;
	for (auto node : list) {
		str << node;
		if (i != list.size()-1)
			str << ", ";
		++i;
	}
	str << "}" << std::endl;
	return str;
}

#endif
