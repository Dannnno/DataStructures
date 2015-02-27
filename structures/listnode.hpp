/**
 * \file listnode.hpp
 * \brief Implementation of a listnode, used in list types.  
 */

#ifndef LISTNODE_HPP
#define LISTNODE_HPP 1

#include <string>
#include <cstddef>



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
	void setNext();

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
	void setValue();

private:
	T value_;
	ListNode<T>* next_;
};