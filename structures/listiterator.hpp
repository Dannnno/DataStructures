/**
 * \file listiterator.hpp
 * \brief Base implementation of list iterators.
 */

#ifndef LISTITERATOR_HPP
#define LISTITERATOR_HPP 1

#include <iterator>

#include "listnode.hpp"


/**
 * \brief Underlying iterator class.
 */
template <typename T>
class ListIterator : std::iterator
{
public:
    
    typedef std::forward_iterator_tag iterator_category;

    /**
     * \brief The default constructor.
     */
    ListIterator() : current_(nullptr) {}

    /**
     * \brief All iterators should have a current node.
     */
    ListIterator(ListNode<T>* node);
	
	/**
	 * \brief Prefix increment operator overloading.
	 */
	ListIterator<T>& operator++();

	/**
	 * \brief Postfix increment operator overloading.
	 */
	ListIterator<T> operator++(int) const;

	/**
	 * \brief Dereferencing operator overloading.
	 */
	const ListNode<T>& operator*() const;

	/**
	 * \brief Member access operator overriding.
	 */
	const ListNode<T>* operator->() const;

	/**
	 * \brief Equality operator overriding.
	 */
	bool operator==(const ListIterator<T>& rhs) const;

	/**
	 * \brief Inequality operator overriding.
	 */
	bool operator!=(const ListIterator<T>& rhs) const;

private:
	ListNode<T>* current_;
};

/**
 * \brief Underlying ConstListIterator class.
 * \remarks Constant versions of everything provided in ListIterator.
 */
template <typename T>
class ConstListIterator : std::iterator
{
public:
    typedef std::forward_iterator_tag iterator_category;
    ConstListIterator() : current_(nullptr) {}
    ConstListIterator(ListNode<T>* node);
    ConstListIterator& operator++();
    ConstListIterator operator++(int) const;
    const ListNode<T>& operator*() const;
    const ListNode<T>* operator->() const;
    bool operator==(const ConstListIterator<T>& rhs) const;
    bool operator!=(const ConstListIterator<T>& rhs) const;

private:
	ListNode<T>* current_;
};

template <typename T> inline
ListIterator<T>::ListIterator(ListNode<T>* node) : current_(node) {
}

template <typename T> inline
ConstListIterator<T>::ConstListIterator(ListNode<T>* node) : 
	current_(node) {
}

template <typename T> inline
ListIterator<T>& ListIterator<T>::operator++()
{
	current_ = current_->getNext();
	return *this;
}

template <typename T> inline
ListIterator<T> ListIterator<T>::operator++(int) const
{
	
    auto old = current_;
    current_ = current_->getNext();
    return ListIterator<T>(old);
}

template <typename T> inline
ConstListIterator<T>& ConstListIterator<T>::operator++()
{
	current_ = current_->getNext();
	return *this;
}

template <typename T> inline
ConstListIterator<T> ConstListIterator<T>::operator++(int) const
{
    auto old = current_;
    current_ = current_->getNext();
    return ConstListIterator<T>(old);
}

template <typename T> inline
const ListNode<T>& ListIterator<T>::operator*() const
{
	return *current_;
}

template <typename T> inline
const ListNode<T>& ConstListIterator<T>::operator*() const
{
	return *current_;
}

template <typename T> inline
const ListNode<T>* ListIterator<T>::operator->() const
{
	return current_;
}

template <typename T> inline
const ListNode<T>* ConstListIterator<T>::operator->() const
{
	return current_;
}

template <typename T> inline
bool ListIterator<T>::operator==(const ListIterator<T>& rhs) const
{
	return current_ == rhs.current_;
}

template <typename T> inline
bool ConstListIterator<T>::operator==(const ConstListIterator<T>& rhs) const
{
	return current_ == rhs.current_;
}

template <typename T> inline
bool ListIterator<T>::operator!=(const ListIterator<T>& rhs) const
{
	if (rhs == nullptr)
		return false;
	return current_ != rhs.current_;
}

template <typename T> inline
bool ConstListIterator<T>::operator!=(const ConstListIterator<T>& rhs) const
{
	if (rhs == nullptr)
		return false;
	return current_ != rhs.current_;
}

#endif
