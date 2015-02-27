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

#include "listnode.hpp"
#include "list.hpp"
#include "listiterator.hpp"
#include "../exceptions.hpp"


/**
 * \brief A paramaterized singly-linked list
 */
template <typename T>
class LinkedList;

template <typename T>
class LinkedList : public List<T>
{
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
     * \brief Returns the start of the ListIterator<T>.
     */
	ListIterator<T> begin();

	/**
	 * \brief Returns the end of the ListIterator<T>.
	 */
    ListIterator<T> end();

    /** 
     * \brief Returns a costant version of the ListIterator<T> (from the start)
     */
    ConstListIterator<T> begin() const;

    /**
     * \brief Returns a constant version of the ListIterator<T> (at the end).
     */
    ConstListIterator<T> end() const;

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
	std::size_t numElements_;
	ListNode<T>* head_;
	ListNode<T>* tail_;

	/**
	 * \brief getListNodes the *node*, not the *value* at the given index.
	 */
	ListNode<T>* getListNode(std::size_t& index)
	{
		ListNode<T>* current = head_;
		ListNode<T>* next = nullptr;

		for (size_t i = 0; i < index; ++i) {
			next = current->getNext();
			current = next;
		}

		return current;
	}

	/**
	 * \brief Constant version of getListNode.
	 */	
	ListNode<T>* cGetListNode(const std::size_t& index) const
	{
		ListNode<T>* current = head_;
		ListNode<T>* next = nullptr;

		for (size_t i = 0; i < index; ++i) {
			next = current->getNext();
			current = next;
		}

		return current;
	}
};


template <typename T> inline LinkedList<T>::LinkedList() :
	numElements_(0), head_(nullptr), tail_(nullptr) {
}

template <typename T> inline LinkedList<T>::LinkedList(
	T* arr, std::size_t length) : 
		numElements_(length), head_(nullptr), tail_(nullptr) {
	head_ = new ListNode<T>(arr[0]);
	ListNode<T>* current = nullptr;
	ListNode<T>* next = nullptr;
	current = head_;

	for (std::size_t i = 1; i < length; ++i) {
		next = new ListNode<T>(arr[i]);
		current->setNext(next);
		current = next;
	}
	tail_ = current;
}

template <typename T> inline T& LinkedList<T>::getHead()
{
	return head_->getValue();
}

template <typename T> inline T& LinkedList<T>::getTail()
{
	return tail_->getValue();
}

template <typename T> inline const T& LinkedList<T>::getHead() const
{
	return head_->getValue();
}

template <typename T> inline const T& LinkedList<T>::getTail() const
{
	return tail_->getValue();
}

template <typename T> inline std::size_t LinkedList<T>::size() const
{
	return numElements_;
}

template <typename T> inline bool LinkedList<T>::isEmpty() const
{
	return numElements_ == 0;
}

template <typename T> inline LinkedList<T>::~LinkedList()
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;

	for (std::size_t i = 0; i < numElements_; ++i) {
		next = current->getNext();
		delete current;
		current = next;
	}
}

template <typename T> inline 
void LinkedList<T>::append(T node)
{
	ListNode<T>* newListNode = new ListNode<T>(node);
	if (numElements_ == 0) {
		head_ = newListNode;
		tail_ = head_;
	} else if (numElements_ == 1) {
		head_->setNext(newListNode);
		tail_ = newListNode;
	} else {
		ListNode<T>* last = tail_;
		last->setNext(newListNode);
		tail_ = newListNode;
	}

	++numElements_;
}

template <typename T> inline
void LinkedList<T>::remove()
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, std::string("LinkedList"));

	// Setting it up like this eliminates duplicate code.
	ListNode<T>* newHead = nullptr;
	if (numElements_ > 1) {
		newHead = head_->getNext();
	}
	delete head_;
	head_ = newHead;
	--numElements_;
}

template <typename T> inline
void LinkedList<T>::remove(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, std::string("LinkedList"));

	std::size_t index = n-1;
	ListNode<T>* prev = getListNode(index);
	ListNode<T>* toRemove = prev->getNext();
	ListNode<T>* after = toRemove->getNext();
	delete toRemove;
	prev->setNext(after);
	--numElements_;
}

template <typename T> inline
T LinkedList<T>::pop()
{
	// Setting it up like this eliminates duplicate code.
	ListNode<T>* newHead = nullptr;
	T value;
	if (numElements_ > 1) {
		newHead = head_->getNext();
		value = head_->getValue();
	} else if (numElements_ == 1)
		value = head_->getValue();
	else 
		throw IndexOutOfBoundsException(0, std::string("LinkedList"));
	
	delete head_;
	head_ = newHead;
	--numElements_;
	return value;
}

template <typename T> inline
T LinkedList<T>::pop(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, std::string("LinkedList"));

	std::size_t index = n-1;
	ListNode<T>* prev = getListNode(index);
	ListNode<T>* toRemove = prev->getNext();
	ListNode<T>* after = toRemove->getNext();
	T value = toRemove->getValue();
	delete toRemove;
	prev->setNext(after);
	--numElements_;	
	return value;
}

template <typename T> inline
void LinkedList<T>::insert(std::size_t n, T value)
{
	if (n > numElements_)
		throw IndexOutOfBoundsException(n, std::string("Deque"));

	ListNode<T>* newListNode = new ListNode<T>(value);

	if (numElements_ == 0) {
		head_ = newListNode;
		tail_ = newListNode;
	} else if (numElements_ == n) {
		ListNode<T>* last = tail_;
		last->setNext(newListNode);
		tail_ = newListNode;
	} else if (n == 0) {
		ListNode<T>* first = head_;
		newListNode->setNext(first);
		head_ = newListNode;
	} else {
		std::size_t index = n - 1;
		ListNode<T>* prev = getListNode(index);
		ListNode<T>* toPush = prev->getNext();
		
		prev->setNext(newListNode);
		newListNode->setNext(toPush);
	}
	++numElements_;
}

template <typename T> inline 
T& LinkedList<T>::operator[](std::size_t index)
{
	return getListNode(index)->getValue();
}

template <typename T> inline 
const T& LinkedList<T>::operator[](std::size_t index) const
{
	return cGetListNode(index)->getValue();
}

template <typename T> inline
ListIterator<T> LinkedList<T>::begin() 
{
	return ListIterator<T>(head_);	
}

template <typename T> inline
ListIterator<T> LinkedList<T>::end()
{
	return ListIterator<T>(nullptr);
}

template <typename T> inline
ConstListIterator<T> LinkedList<T>::begin() const 
{
	return ConstListIterator<T>(head_);
}

template <typename T> inline
ConstListIterator<T> LinkedList<T>::end() const
{
	return ConstListIterator<T>(nullptr);
}

template <typename T> inline
void LinkedList<T>::sort() 
{

}

template <typename T> inline
LinkedList<T> LinkedList<T>::sorted() const
{
	return NULL;
}

template <typename T> inline
void LinkedList<T>::reverse()
{

}

template <typename T> inline
LinkedList<T> LinkedList<T>::reversed() const
{
	return NULL;
}

#endif
