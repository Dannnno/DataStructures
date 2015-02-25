/**
 * \file listnode.hpp
 * \author Dan Obermiller
 * \brief Implementation of a list node for a singly linked list.
 * \remarks Uses templates and operator overloading to provide an almost
 * enjoyable interface.
 */

#ifndef LISTNODE_HPP
#define LISTNODE_HPP 1

#include <string>
#include <iostream>

/**
 * \brief A node in a singly linked list.
 */
template <typename T>
class ListNode;

/**
 * \brief Overloads the << operator to allow writing a node's contents
 *  to a string or stream.
 **/
template <typename T> std::ostream& operator<<(
	std::ostream& str, const ListNode<T>& node);

template <typename T>
class ListNode
{
public:
	/**
	 * \brief The default constructor is disabled.
	 */
	ListNode() = delete;

	/**
	 * \brief All nodes must be value initialized.
	 */
	ListNode(T value);

	/**
	 * \brief Constructor that is provided the next node.
	 */
	ListNode(T value, ListNode<T>* node);

	/**
	 * \brief Returns the value within the node.
	 */
	 T& getValue();

	/**
	 * \brief Provides a const reference tot he value.
	 */
	T& getCValue() const;

	/**
	 * \brief Returns a pointer to the next node.
	 * \post The node is unchanged.
	 */
	ListNode* getNext() const;

	/**
	 * \brief Sets the next node in the list.
	 */
	void setNext(ListNode* node);

private:
	T value_;
	ListNode<T>* next_;
};


template <typename T> inline ListNode<T>::ListNode(T value) : 
	value_(value), next_(nullptr) {
}

template <typename T> inline 
ListNode<T>::ListNode(T value, ListNode<T>* node) :
	value_(value), next_(node) {
}

template <typename T> inline T& ListNode<T>::getValue()
{
	return value_;
}

template <typename T> inline T& ListNode<T>::getCValue() const
{
	return value_;
}

template <typename T> inline ListNode<T>* ListNode<T>::getNext() const
{
	return next_;
}

template <typename T> inline 
void ListNode<T>::setNext(ListNode<T>* node) 
{
	next_ = node;
}

template <typename T> inline std::ostream& operator<<(
	std::ostream& str, const ListNode<T>& node)
{
	str << node.getCValue();
	return str;
}

#endif
