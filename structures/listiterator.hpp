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
class ListIterator
{
public:
    
    typedef std::forward_iterator_tag iterator_category;

    /**
     * \brief The default constructor is disabled.
     */
    ListIterator() = delete;

    /**
     * \brief All iterators should have a current node.
     */
    ListIterator(ListNode<T>* node);
	
	/**
	 * \brief Prefix increment operator overloading.
	 */
	ListIterator<T> operator++();

	/**
	 * \brief Postfix increment operator overloading.
	 */
	ListIterator<T> operator++(int);

	/**
	 * \brief Dereferencing operator overloading.
	 */
	ListNode<T>& operator*();

	/**
	 * \brief Member access operator overriding.
	 */
	ListNode<T>* operator->();

	/**
	 * \brief Equality operator overriding.
	 */
	bool operator==(const ListIterator<T>& rhs);

	/**
	 * \brief Inequality operator overriding.
	 */
	bool operator!=(const ListIterator<T>& rhs);

private:
	ListNode<T>* current_;
};

/**
 * \brief Underlying ConstListIterator class.
 * \remarks Constant versions of everything provided in iterator.
 */
template <typename T>
class ConstListIterator
{
public:
    typedef std::forward_iterator_tag iterator_category;
    ConstListIterator() = delete;
    ConstListIterator(ListNode<T>* node);
    ConstListIterator operator++();
    ConstListIterator operator++(int);
    const ListNode<T>& operator*();
    const ListNode<T>* operator->();
    bool operator==(const ConstListIterator<T>& rhs);
    bool operator==(std::nullptr_t& rhs);
    bool operator!=(const ConstListIterator<T>& rhs);

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
ListIterator<T> ListIterator<T>::operator++()
{
	current_ = current_->getNext();
	return *this;
}

template <typename T> inline
ListIterator<T> ListIterator<T>::operator++(int)
{
	current_ = current_->getNext();
	return *this;
}

template <typename T> inline
ConstListIterator<T> ConstListIterator<T>::operator++()
{
	current_ = current_->getNext();
	return *this;
}

template <typename T> inline
ConstListIterator<T> ConstListIterator<T>::operator++(int)
{
	current_ = current_->getNext();
	return *this;
}

template <typename T> inline
ListNode<T>& ListIterator<T>::operator*()
{
	return *current_;
}

template <typename T> inline
const ListNode<T>& ConstListIterator<T>::operator*()
{
	return *current_;
}

template <typename T> inline
ListNode<T>* ListIterator<T>::operator->()
{
	return current_;
}

template <typename T> inline
const ListNode<T>* ConstListIterator<T>::operator->()
{
	return current_;
}

template <typename T> inline
bool ListIterator<T>::operator==(const ListIterator<T>& rhs)
{
	return current_ == rhs.current_;
}

template <typename T> inline
bool ConstListIterator<T>::operator==(const ConstListIterator<T>& rhs)
{
	return current_ == rhs.current_;
}

template <typename T> inline
bool ListIterator<T>::operator!=(const ListIterator<T>& rhs)
{
	return current_ != rhs.current_;
}

template <typename T> inline
bool ConstListIterator<T>::operator!=(const ConstListIterator<T>& rhs)
{
	return current_ != rhs.current_;
}

#endif
