/**
 * \file linkedlist.hpp
 * \author Dan Obermiller
 * \brief Implementation of a singly-linked list.
 * \remarks Uses templates and operator overloading to provide an almost
 * enjoyable interface.
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP 1

#include <cstddef>
#include <string>
#include <iostream>

#include "listnode.hpp"


template <typename T>
class LinkedList;

/**
 * \brief Overloading the << operator to allow clean string 
 *        representations of the linkedlist.
 */
template <typename T> 
std::ostream& operator<<(std::ostream& str, const LinkedList<T>& list);


template <typename T>
/**
 * \brief A paramaterized singly-linked list
 */
class LinkedList
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
	T getHead() const;

	/**
	 * \brief The tail (last item) of the list.
	 */
	T getTail() const;

	/**
	 * \brief Adds a node to the end of the list.
	 * \post All nodes have the appropriate "next_" and the list has
	 *		 the appropriate size.
	 */
	void append(T value);

	/**
	 * \brief Overloads the mutable subscript operator.
	 */
    T& operator[](size_t index);

    /**
     * \brief Overloads the immutable subscript operator.
     */
  	const T& operator[](size_t index) const;

  	/**
  	 * \brief Returns the size of the list
  	 */
  	std::size_t size() const;

  	/**
  	 * \brief Returns whether or not the list is empty.
  	 */
	bool isEmpty() const;

private:
	std::size_t numElements_;
	ListNode<T>* head_;
	ListNode<T>* tail_;
};


template <typename T> inline LinkedList<T>::LinkedList() :
	numElements_(0), head_(nullptr), tail_(nullptr) {
}

template <typename T> inline LinkedList<T>::LinkedList(
	T* arr, std::size_t length) : 
		numElements_(length), head_(nullptr), tail_(nullptr) {
	ListNode<T>* h = new ListNode<T>(arr[0]);
	head_ = h;
	ListNode<T>* current = head_;
	for (std::size_t i = 1; i < length; ++i) {
		ListNode<T>* next = new ListNode<T>(arr[i]);
		current->setNext(next);
		current = next;
	}
	tail_ = current;
}

template <typename T> inline LinkedList<T>::~LinkedList()
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;
	while (current != nullptr) {
		next = head_->getNext();
		delete current;
		current = next;
	}
}

template <typename T> inline T LinkedList<T>::getHead() const
{
	return head_->getValue();
}

template <typename T> inline T LinkedList<T>::getTail() const
{
	return tail_->getValue();
}

template <typename T> inline 
void LinkedList<T>::append(T node)
{
	ListNode<T>* newNode = new ListNode<T>(node);
	if (numElements_ == 0) {
		head_ = newNode;
		tail_ = head_;
	} else if (numElements_ == 1) {
		head_->setNext(newNode);
		tail_ = newNode;
	} else {
		ListNode<T>* last = tail_;
		last->setNext(newNode);
		tail_ = newNode;
	}

	++numElements_;
}

template <typename T> inline 
T& LinkedList<T>::operator[](size_t index)
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;

	for (size_t i = 0; i < index; ++i) {
		next = current->getNext();
		current = next;
	}

	T retValue = current->getValue();
	T& retRef = retValue;
	return retRef;
}

template <typename T> inline 
const T& LinkedList<T>::operator[](size_t index) const
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;

	for (size_t i = 0; i < index; ++i) {
		next = current->getNext();
		current = next;
	}

	const T value = current->getValue();
	const T& valRef = value;
	return valRef;
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
std::ostream& operator<<(std::ostream& str, const LinkedList<T>& list)
{
	str << "{";
	for (size_t i = 0; i < list.size()-1; ++i) {
		str << list[i] << ", ";
	}
	str << list.getTail() << "}";
	return str;
}

#endif
