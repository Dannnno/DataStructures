/**
 * \file _deque.hpp
 * \brief Private implementation file for a doubly linked list.
 */

#ifndef _DEQUE_HPP
#define _DEQUE_HPP 1

#include <cstddef>
#include <string>
#include <iostream>
#include <iterator>
#include <utility>

#include "list.hpp"
#include "../exceptions.hpp"

template <typename T> inline Deque<T>::Deque() :
	numElements_{0}, head_{nullptr}, tail_{nullptr} {
}

template <typename T> inline Deque<T>::Deque(
	T* arr, std::size_t length) : 
		numElements_{length}, 
		head_{new ListNode{arr[0], nullptr, nullptr}}, 
		tail_{nullptr} {

	ListNode* current = head_;
	ListNode* next = nullptr;

	for (std::size_t i = 1; i < length; ++i) {
		next = new ListNode{arr[i], nullptr, current};
		current->next_ = next;
		current = next;
	}
	tail_ = current;
}

template <typename T> inline 
Deque<T>::Deque(const Deque<T>& orig) :
	numElements_{0},
	head_{nullptr},
	tail_{nullptr} 
{
	for (T node : orig)
		append(node);
}

template <typename T> inline
void swap(Deque<T>& first, Deque<T>& second)
{
	std::swap(first.head_, second.head_);
	std::swap(first.tail_, second.tail_);
	std::swap(first.numElements_, second.numElements_);
}

template <typename T> inline
Deque<T>::Deque(Deque<T>&& other) :
	numElements_{0},
	head_{nullptr},
	tail_{nullptr}
{
	swap(*this, other);
}

template <typename T> inline
Deque<T>& Deque<T>::operator=(Deque<T> rhs)
{
	swap(*this, rhs);
	return *this;
}

template <typename T> inline Deque<T>::~Deque()
{
	while (!isEmpty())
		remove();
}

template <typename T> inline T& Deque<T>::getHead()
{
	if (head_ != nullptr)
		return head_->value_;
	else
		throw IndexOutOfBoundsException(0, "Deque");
}

template <typename T> inline T& Deque<T>::getTail()
{
	if (tail_ != nullptr)
		return tail_->value_;
	else
		throw IndexOutOfBoundsException(0, "Deque");
}

template <typename T> inline const T& Deque<T>::getHead() const
{
	if (head_ != nullptr)
		return head_->value_;
	else
		throw IndexOutOfBoundsException(0, "Deque");
}

template <typename T> inline const T& Deque<T>::getTail() const
{
	if (tail_ != nullptr)
		return tail_->value_;
	else
		throw IndexOutOfBoundsException(0, "Deque");
}

template <typename T> inline std::size_t Deque<T>::size() const
{
	return numElements_;
}

template <typename T> inline bool Deque<T>::isEmpty() const
{
	return numElements_ == 0;
}

template <typename T> inline 
void Deque<T>::append(T node)
{
	if (numElements_ == 0) {
		ListNode* newListNode = new ListNode{node, nullptr, nullptr};
		head_ = newListNode;
		tail_ = head_;
	} else if (numElements_ == 1) {
		ListNode* newListNode = new ListNode{node, nullptr, head_};
		head_->next_ = newListNode;
		tail_ = newListNode;
	} else {
		ListNode* newListNode = new ListNode{node, nullptr, tail_};
		tail_->next_ = newListNode;
		tail_ = newListNode;
	}

	++numElements_;
}

template <typename T> inline
void Deque<T>::appendLeft(T node)
{
	if (numElements_ == 0) {
		append(node);
	} else {
		ListNode* newListNode = new ListNode{node, head_, nullptr};
		head_->previous_ = newListNode;
		head_ = newListNode;

		++ numElements_;
	}
}

template <typename T> inline
void Deque<T>::remove()
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, "Deque");

	// Setting it up like this eliminates duplicate code.
	ListNode* newHead = nullptr;
	if (numElements_ > 1) {
		newHead = head_->next_;
		newHead->previous_ = nullptr;
	}
	delete head_;
	head_ = newHead;
	--numElements_;
}

template <typename T> inline
void Deque<T>::remove(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, "Deque");

	ListNode* toRemove = getListNode(n);
	ListNode* prev = toRemove->previous_;
	ListNode* after = toRemove->next_;

	prev->next_ = after;
	after->previous_ = prev;
	--numElements_;
	delete toRemove;
}

template <typename T> inline
T Deque<T>::pop()
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
		throw IndexOutOfBoundsException(0, "Deque");
	
	delete head_;

	head_ = newHead;
	head_->previous_ = nullptr;
	--numElements_;

	return value;
}

template <typename T> inline
T Deque<T>::pop(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, "Deque");

	ListNode* toRemove = getListNode(n);
	ListNode* prev = toRemove->previous_;
	ListNode* after = toRemove->next_;

	prev->next_ = after;
	after->previous_ = prev;
	--numElements_;
	T value = toRemove->value_;
	delete toRemove;
	return value;
}

template <typename T> inline
void Deque<T>::insert(std::size_t n, T value)
{
	if (n > numElements_)
		throw IndexOutOfBoundsException(n, "Deque");
	else if (numElements_ == n)
		append(value);
	else if (n == 0)
		appendLeft(value);
	else {
		ListNode* toPush = getListNode(n);
		ListNode* prev = toPush->previous_;
		ListNode* newListNode = new ListNode{value, toPush, prev};

		prev->next_ = newListNode;
		toPush->previous_ = newListNode;

		++numElements_;
	}
}

template <typename T> inline
bool Deque<T>::contains(T const& value) const
{
	for (T node : *this)
		if (node == value)
			return true;
	return false;
}

template <typename T> inline
std::size_t Deque<T>::index_of(T const& value) const
{
	std::size_t i = 0;
	for (T node : *this) {
		if (node == value)
			return i;
		++i;
	}

	throw IndexOutOfBoundsException(numElements_, "Deque");
}

template <typename T> inline
Deque<T> operator+(Deque<T> lhs, Deque<T> rhs)
{
	lhs.numElements_ += rhs.numElements_;
	lhs.tail_->next_ = rhs.head_;
	rhs.head_->previous_ = lhs.tail_;
	lhs.tail_ = rhs.tail_;
	// This bypasses the destructor on rhs, preventing it from double-deleting
	rhs.numElements_ = 0;
	return lhs;
}

template <typename T> inline
Deque<T> operator*(Deque<T> lhs, std::size_t n)
{
	Deque<T> orig{lhs};

	// We start at one because both 0 and 1 are being considered identity values
	// for this operator.
	for (std::size_t i = 1; i < n; ++i) {
		lhs = lhs + orig;
	}
	return lhs;
}

template <typename T> inline
T* Deque<T>::asArray() const
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
T& Deque<T>::operator[](std::size_t index)
{
	return getListNode(index)->value_;
}

template <typename T> inline 
const T& Deque<T>::operator[](std::size_t index) const
{
	return getListNode(index)->value_;
}

template <typename T> inline 
bool Deque<T>::operator==(const Deque<T>& rhs) const
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
bool Deque<T>::operator!=(const Deque<T>& rhs) const
{
	return !(*this == rhs);
}

template <typename T> inline
typename Deque<T>::iterator Deque<T>::begin() 
{
	return Iterator{head_};	
}

template <typename T> inline
typename Deque<T>::iterator Deque<T>::end()
{
	return Iterator{nullptr};
}

template <typename T> inline
typename Deque<T>::const_iterator Deque<T>::begin() const 
{
	return ConstIterator{head_};
}

template <typename T> inline
typename Deque<T>::const_iterator Deque<T>::end() const
{
	return ConstIterator{nullptr};
}

template <typename T> inline
typename Deque<T>::reverse_iterator Deque<T>::rbegin() 
{
	return ReverseIterator{tail_};	
}

template <typename T> inline
typename Deque<T>::reverse_iterator Deque<T>::rend()
{
	return ReverseIterator{nullptr};
}

template <typename T> inline
typename Deque<T>::const_reverse_iterator Deque<T>::rbegin() const 
{
	return ConstReverseIterator{tail_};
}

template <typename T> inline
typename Deque<T>::const_reverse_iterator Deque<T>::rend() const
{
	return ConstReverseIterator{nullptr};
}

template <typename T> inline
void Deque<T>::sort() // Uses a mergesort algorithm
{

}

template <typename T> inline
Deque<T> Deque<T>::sorted() const
{
	Deque<T> newList;
	return newList;
}

template <typename T> inline
void Deque<T>::reverse()
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
		current->previous_ = next;
		previous = current;
		current = next;
		++i;
	}

	head_ = last;
	tail_ = first;
}

template <typename T> inline
Deque<T> Deque<T>::reversed() const
{
	Deque<T> reversedList;
	if (numElements_ == 0)
		return reversedList;

	for (const_reverse_iterator rit = rbegin(); rit != rend(); ++rit) 
		reversedList.append(*rit);

	return reversedList;
}

template <typename T> inline
T* Deque<T>::toArray() const
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, "Deque");

	T* newArray = new T[numElements_];
	std::size_t i = 0;

	for (T node : *this) {
		newArray[i] = node;
		++i;
	}
	
	return newArray;
}

template <typename T> inline
typename Deque<T>::iterator&
Deque<T>::iterator::operator++()
{
	current_ = current_->next_;
	return *this;
}

template <typename T> inline
typename Deque<T>::const_iterator& 
Deque<T>::const_iterator::operator++()
{
	current_ = current_->next_;
	return *this;
}

template <typename T> inline
typename Deque<T>::reverse_iterator&
Deque<T>::reverse_iterator::operator++()
{
	current_ = current_->previous_;
	return *this;
}

template <typename T> inline
typename Deque<T>::const_reverse_iterator& 
Deque<T>::const_reverse_iterator::operator++()
{
	current_ = current_->previous_;
	return *this;
}

template <typename T> inline
typename Deque<T>::iterator
Deque<T>::iterator::operator++(int) const
{
    auto old = current_;
    current_ = current_->next_;
    return Iterator{old};
}

template <typename T> inline
typename Deque<T>::const_iterator
Deque<T>::const_iterator::operator++(int) const
{
    auto old = current_;
    current_ = current_->next_;
    return Iterator{old};
}

template <typename T> inline
typename Deque<T>::reverse_iterator
Deque<T>::reverse_iterator::operator++(int) const
{
    auto old = current_;
    current_ = current_->previous_;
    return Iterator{old};
}

template <typename T> inline
typename Deque<T>::const_reverse_iterator
Deque<T>::const_reverse_iterator::operator++(int) const
{
    auto old = current_;
    current_ = current_->previous_;
    return Iterator{old};
}

template <typename T> inline
const T& Deque<T>::iterator::operator*() const
{
	return current_->value_;
}

template <typename T> inline
const T& Deque<T>::const_iterator::operator*() const
{
	return current_->value_;
}

template <typename T> inline
const T& Deque<T>::reverse_iterator::operator*() const
{
	return current_->value_;
}

template <typename T> inline
const T& Deque<T>::const_reverse_iterator::operator*() const
{
	return current_->value_;
}

template <typename T> inline
const T* Deque<T>::iterator::operator->() const
{
	return current_->value_;
}

template <typename T> inline
const T* Deque<T>::const_iterator::operator->() const
{
	return current_->value_;
}

template <typename T> inline
const T* Deque<T>::reverse_iterator::operator->() const
{
	return current_->value_;
}

template <typename T> inline
const T* Deque<T>::const_reverse_iterator::operator->() const
{
	return current_->value_;
}

template <typename T> inline
bool Deque<T>::iterator::operator==(const iterator& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T> inline
bool Deque<T>::const_iterator::operator==(const const_iterator& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T> inline
bool Deque<T>::reverse_iterator::operator==(const reverse_iterator& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T> inline
bool Deque<T>::const_reverse_iterator::operator==(
	const const_reverse_iterator& rhs) const
{
	return current_ == rhs.current_;
} 

template <typename T> inline
bool Deque<T>::iterator::operator!=(const iterator& rhs) const
{
	return !(*this == rhs);
} 

template <typename T> inline
bool Deque<T>::const_iterator::operator!=(
	const const_iterator& rhs) const
{
	return !(*this == rhs);
} 

template <typename T> inline
bool Deque<T>::reverse_iterator::operator!=(const reverse_iterator& rhs) const
{
	return !(*this == rhs);
} 

template <typename T> inline
bool Deque<T>::const_reverse_iterator::operator!=(
	const const_reverse_iterator& rhs) const
{
	return !(*this == rhs);
} 

template <typename T> inline 
std::ostream& operator<<(std::ostream& str, const Deque<T>& list)
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

template <typename T> inline
typename Deque<T>::ListNode* Deque<T>::getListNode(
	std::size_t index) const
{
	if (index >= numElements_)
		throw IndexOutOfBoundsException(index, "Deque");
	else if (index > numElements_ / 2) {
		const_reverse_iterator it = rbegin();
		index = numElements_ - index - 1;
		std::advance(it, index);
		return it.current_;
	} else {
		const_iterator it = begin();
		std::advance(it, index);
		return it.current_;
	}
}

#endif