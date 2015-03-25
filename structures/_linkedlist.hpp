/**
 * \file _linkedlist.hpp
 * \brief Private implementation file for a linkedlist.
 */

#ifndef _LINKEDLIST_HPP
#define _LINKEDLIST_HPP 1

#include <cstddef>
#include <string>
#include <iostream>
#include <iterator>
#include <utility>

#include "list.hpp"
#include "../exceptions.hpp"

template <typename T> inline LinkedList<T>::LinkedList() :
	numElements_{0}, head_{nullptr}, tail_{nullptr} {
}

template <typename T> inline LinkedList<T>::LinkedList(
	T* arr, std::size_t length) : 
		numElements_{length}, 
		head_{new ListNode{arr[0], nullptr}}, 
		tail_{nullptr} {

	ListNode* current{head_};
	ListNode* next = nullptr;

	for (std::size_t i = 1; i < length; ++i) {
		next = new ListNode{arr[i], nullptr};
		current->next_ = next;
		current = next;
	}
	tail_ = current;
}

template <typename T> inline 
LinkedList<T>::LinkedList(const LinkedList<T>& orig) :
	numElements_{0},
	head_{nullptr},
	tail_{nullptr} 
{
	for (T node : orig)
		append(node);
}

template <typename T> inline
void swap(LinkedList<T>& first, LinkedList<T>& second)
{
	std::swap(first.head_, second.head_);
	std::swap(first.tail_, second.tail_);
	std::swap(first.numElements_, second.numElements_);
}

template <typename T> inline
LinkedList<T>::LinkedList(LinkedList<T>&& other) :
	numElements_{0},
	head_{nullptr},
	tail_{nullptr}
{
	swap(*this, other);
}

template <typename T> inline
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> rhs)
{
	swap(*this, rhs);
	return *this;
}

template <typename T> inline LinkedList<T>::~LinkedList()
{
	while (!isEmpty())
		remove();
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
LinkedList<T> operator+(LinkedList<T> lhs, LinkedList<T> rhs)
{
	lhs.numElements_ += rhs.numElements_;
	lhs.tail_->next_ = rhs.head_;
	lhs.tail_ = rhs.tail_;
	// This bypasses the destructor on rhs, preventing it from double-deleting
	rhs.numElements_ = 0;
	return lhs;
}

template <typename T> inline
LinkedList<T> operator*(LinkedList<T> lhs, std::size_t n)
{
	LinkedList<T> orig{lhs};
	
	// We start at one because both 0 and 1 are being considered identity values
	// for this operator.
	for (std::size_t i = 1; i < n; ++i) {
		lhs = lhs + orig;
	}
	return lhs;
}

template <typename T> inline
T* LinkedList<T>::asArray() const
{
	T* arr = new T[numElements_];
	ListNode* current = head_;
	for (std::size_t i = 0; i < numElements_; ++i) {
		arr[i] = current->value_;
		current = current->next_;
	}

	return arr;
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
	ListNode* first = head_;
	ListNode* last = tail_;

	ListNode* current = head_;
	ListNode* previous = nullptr;
	ListNode* next = nullptr;

	std::size_t i = 0;

	while (i < numElements_) {
		next = current->next_;
		current->next_ = previous;
		previous = current;
		current = next;
		++i;
	}

	head_ = last;
	tail_ = first;
}

template <typename T> inline
LinkedList<T> LinkedList<T>::reversed() const
{
	LinkedList<T> reversedList;
	if (numElements_ == 0)
		return reversedList;

	ListNode* current_ = head_;

	for (std::size_t i = 0; i < numElements_; ++i) {
		reversedList.insert(0, current_->value_);
		current_ = current_->next_;
	}

	return reversedList;
}

template <typename T> inline
T* LinkedList<T>::toArray() const
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, "LinkedList");

	T* newArray = new T[numElements_];
	std::size_t i = 0;

	for (T node : *this) {
		newArray[i] = node;
		++i;
	}
	
	return newArray;
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