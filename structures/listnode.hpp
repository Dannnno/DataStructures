/**
 * \file listnode.hpp
 * \brief Implementation of a listnode, used in list types.  
 */

#ifndef LISTNODE_HPP
#define LISTNODE_HPP 1

#include <string>
#include <cstddef>


/**
 * \brief Base listnode class.  Supports all functionality required by
 *  	  the List API.
 */
template <typename T> struct ListNode;

/**
 * \brief Overloading the << operator.
 */
template <typename T>
std::ostream& operator<<(std::ostream& str, const ListNode<T>& node);

template <typename T>
struct ListNode {
public:

	/**
	 * \brief Disables the default constructor.
	 */
	ListNode() = delete;

	/**
	 * \brief All ListNodes should be value initialized.
	 */
	ListNode(T value);

	/**
	 * \brief Returns a pointer to the next node
	 */
	ListNode<T>* getNext();

	/**
	 * \brief Sets the next node.
	 */
	void setNext(ListNode<T>* node);

	/**
	 * \brief Returns the value.
	 */
	T& getValue();

	/**
	 * \brief Returns a const reference to the value.
	 */
	const T& getCValue() const;

	/**
	 * \brief Sets the value of the node.
	 */
	void setValue(T value);

private:
	T value_;
	ListNode<T>* next_;
};


template <typename T> inline
ListNode<T>::ListNode(T value) : value_(value) {
}

template <typename T> inline
ListNode<T>* ListNode<T>::getNext()
{
	return next_;
}

template <typename T> inline
void ListNode<T>::setNext(ListNode<T>* node)
{
	next_ = node;
}

template <typename T> inline
T& ListNode<T>::getValue()
{
	return value_;
}

template <typename T> inline
const T& ListNode<T>::getCValue() const 
{
	return value_;
}

template <typename T> inline
void ListNode<T>::setValue(T value)
{
	value_ = value;
}

template <typename T>
std::ostream& operator<<(std::ostream& str, const ListNode<T>& node)
{
	str << node.getCValue();
	return str;
}

#endif
