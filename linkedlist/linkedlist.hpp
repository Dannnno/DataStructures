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
#include "../exceptions.hpp"


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
	 * \brief Overloads the mutable subscript operator.
	 */
    T& operator[](std::size_t index);

    /**
     * \brief Overloads the immutable subscript operator.
     */
  	const T& operator[](std::size_t index) const;

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

	/**
	 * \brief Gets the *node*, not the *value* at the given index.
	 */
	ListNode<T>* get(std::size_t& index);

	/**
	 * \brief Constant version of get.
	 */
	ListNode<T>* cGet(const std::size_t& index) const;
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

template <typename T> inline LinkedList<T>::~LinkedList()
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;
	while (current != nullptr) {
		next = current->getNext();
		delete current;
		current = next;
	}
}

template <typename T> inline T& LinkedList<T>::getHead()
{
	return head_->getValue();
}

template <typename T> inline T& LinkedList<T>::getTail()
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
	ListNode<T>* prev = get(index);
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
	} else if (numElements_ == 0) {
		throw IndexOutOfBoundsException(0, std::string("LinkedList"));
	}
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
	ListNode<T>* prev = get(index);
	ListNode<T>* toRemove = prev->getNext();
	ListNode<T>* after = toRemove->getNext();
	T value = toRemove->getValue();
	delete toRemove;
	prev->setNext(after);
	--numElements_;	
	return value;
}

template <typename T> inline
ListNode<T>* LinkedList<T>::get(std::size_t& index)
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;

	for (size_t i = 0; i < index; ++i) {
		next = current->getNext();
		current = next;
	}

	return current;
}

template <typename T> inline
ListNode<T>* LinkedList<T>::cGet(const std::size_t& index) const
{
	ListNode<T>* current = head_;
	ListNode<T>* next = nullptr;

	for (size_t i = 0; i < index; ++i) {
		next = current->getNext();
		current = next;
	}

	return current;
}	

template <typename T> inline 
T& LinkedList<T>::operator[](std::size_t index)
{
	return get(index)->getValue();
}

template <typename T> inline 
const T& LinkedList<T>::operator[](std::size_t index) const
{
	return cGet(index)->getCValue();
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
	for (size_t i = 0; i < list.size(); ++i) {
		str << list[i];
		if (i != list.size()-1) 
			str << ", ";
	}
	str << "}" << std::endl;
	return str;
}

#endif
