/**
 * \file list.hpp
 * \author Dan Obermiller
 * \brief Abstract base class of list types.
 */

#ifndef LIST_HPP
#define LIST_HPP 1

#include <cstddef>
#include <string>
#include <iostream>

#include "../exceptions.hpp"


template <typename T>
class List;

/**
 * \brief Overloading the << operator to allow clean string 
 *        representations of the list.
 */
template <typename T> virtual
std::ostream& operator<<(std::ostream& str, const List<T>& list);


template <typename T>
/**
 * \brief A paramaterized doubly linked list
 */
class List
{
public:

	/**
	 * \brief A default constructor.
	 */
	virtual List() = 0;

	/**
	 * \brief A constructor from an array.
	 */
	virtual List(T* arr, std::size_t length) = 0;

	/**
	 * \brief The destructor.
	 */
	virtual ~List() {}

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
	virtual void append(T value) = 0;

	/**
	 * \brief Removes the first item in the list.
	 */
	virtual void remove() = 0;

	/**
	 * \brief Removes the nth item in the list.
	 */
	virtual void remove(std::size_t n) = 0;

	/**
	 * \brief Removes and returns a copy of the value of the first item 
	 *        in the list.
	 */
	virtual T pop() = 0;

	/**
	 * \brief Removes and returns a copy of the value of the nth item 
	 *		  in the list.
	 */
	virtual T pop(std::size_t n) = 0;

	/**
	 * \brief inserts an item at the indicated index.
	 */
	virtual void insert(std::size_t index, T value) = 0;

	/**
	 * \brief Overloads the mutable subscript operator.
	 */
    virtual T& operator[](std::size_t index) = 0;

    /**
     * \brief Overloads the immutable subscript operator.
     */
  	virtual const T& operator[](std::size_t index) const = 0;

  	/**
  	 * \brief Returns the size of the list
  	 */
  	std::size_t size() const;

  	/**
  	 * \brief Returns whether or not the list is empty.
  	 */
	bool isEmpty() const;

private:
	template <typename TYPE> static
	struct ListNode 
	{
		TYPE value_;
		Node<TYPE>* previous_;
		Node<TYPE>* next_;
		Node() = delete;
		Node(TYPE value) : 
			value_(value), previous_(nullptr), next_(nullptr) {}
	};

	std::size_t numElements_;
	Node<T>* head_;
	Node<T>* tail_;

	/**
	 * \brief getNodes the *node*, not the *value* at the given index.
	 */
	Node<T>* getNode(std::size_t& index)
	{
		Node<T>* current = head_;
		Node<T>* next = nullptr;

		for (size_t i = 0; i < index; ++i) {
			next = current->next_;
			current = next;
		}

		return current;
	}

	/**
	 * \brief Constant version of getNode.
	 */
	Node<T>* cgetNode(const std::size_t& index) const
	{
		Node<T>* current = head_;
		Node<T>* next = nullptr;

		for (size_t i = 0; i < index; ++i) {
			next = current->next_;
			current = next;
		}

		return current;
	}
};


template <typename T> inline List<T>::List() :
	numElements_(0), head_(nullptr), tail_(nullptr) {
}

template <typename T> inline List<T>::List(
	T* arr, std::size_t length) : 
		numElements_(length), head_(nullptr), tail_(nullptr) {
	head_ = new Node<T>(arr[0]);

	Node<T>* current = nullptr;
	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;

	current = head_;
	for (std::size_t i = 1; i < length; ++i) {
		next = new Node<T>(arr[i]);
		current->next_ = next;
		current->previous_ = previous;
		previous = current;
		current = next;
	}
	tail_ = current;
	tail_->previous_ = previous;
}

template <typename T> inline List<T>::~List()
{
	Node<T>* current = head_;
	Node<T>* next = nullptr;
	while (current != nullptr) {
		next = current->next_;
		delete current;
		current = next;
	}
}

template <typename T> inline T& List<T>::getHead()
{
	return head_->value_;
}

template <typename T> inline T& List<T>::getTail()
{
	return tail_->value_;
}

template <typename T> inline 
void List<T>::append(T node)
{
	Node<T>* newNode = new Node<T>(node);
	if (numElements_ == 0) {
		head_ = newNode;
		tail_ = head_;
	} else if (numElements_ == 1) {
		head_->next_ = newNode;
		newNode->previous_ = head_;
		tail_ = newNode;
	} else {
		Node<T>* last = tail_;
		last->next_ = newNode;
		newNode->previous_ = last;
		tail_ = newNode;
	}

	++numElements_;
}

template <typename T> inline
void List<T>::appendLeft(T node)
{
	Node<T>* newNode = new Node<T>(node);
	if (numElements_ == 0) {
		head_ = newNode;
		tail_ = head_;
	} else if (numElements_ == 1) {
		tail_ = head_;
		head_ = newNode;
		head_->next_ = tail_;
		tail_->previous_ = head_;
	} else {
		Node<T>* first = head_;
		first->previous_ = newNode;
		newNode->next_ = first;
		head_ = newNode;
	}

	++numElements_;
}

template <typename T> inline
void List<T>::remove()
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, std::string("List"));

	// Setting it up like this eliminates duplicate code.
	Node<T>* newHead = nullptr;
	if (numElements_ > 1) {
		newHead = head_->next_;
	}
	delete head_;
	head_ = newHead;
	head_->previous_ = nullptr;
	--numElements_;
}

template <typename T> inline
void List<T>::remove(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, std::string("List"));

	std::size_t index = n-1;
	Node<T>* prev = getNode(index);
	Node<T>* toRemove = prev->next_;
	Node<T>* after = toRemove->next_;
	delete toRemove;
	prev->next_ = after;
	after->previous_ = prev;
	--numElements_;
}

template <typename T> inline
T List<T>::pop()
{
	// Setting it up like this eliminates duplicate code.
	Node<T>* newHead = nullptr;
	T value;
	if (numElements_ > 1) {
		newHead = head_->next_;
		value = head_->value_;
	} else if (numElements_ == 1)
		value = head_->value_;
	else
		throw IndexOutOfBoundsException(0, std::string("List"));
	
	delete head_;
	head_ = newHead;
	head_->previous_ = nullptr;
	--numElements_;
	return value;
}

template <typename T> inline
T List<T>::pop(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, std::string("List"));

	std::size_t index = n - 1;
	Node<T>* prev = getNode(index);
	Node<T>* toRemove = prev->next_;
	Node<T>* after = toRemove->next_;
	T value = toRemove->value_;
	delete toRemove;
	prev->next_ = after;
	after->previous_ = prev;
	--numElements_;	
	return value;
}	

template <typename T> inline
void List<T>::insert(std::size_t n, T value)
{
	if (n > numElements_)
		throw IndexOutOfBoundsException(n, std::string("List"));

	Node<T>* newNode = new Node<T>(value);

	if (numElements_ == 0) {
		head_ = newNode;
		tail_ = newNode;
	} else if (numElements_ == n) {
		Node<T>* last = tail_;
		last->next_ = newNode;
		newNode->previous_ = last;
		tail_ = newNode;
	} else if (n == 0) {
		Node<T>* first = head_;
		newNode->next_ = first;
		first->previous_ = newNode;
		head_ = newNode;
	} else {
		std::size_t index = n - 1;
		Node<T>* prev = getNode(index);
		Node<T>* toPush = prev->next_;

		prev->next_ = newNode;
		newNode->previous_ = prev;
		toPush->previous_ = newNode;
		newNode->next_ = toPush;
	}
	++numElements_;
}

template <typename T> inline 
T& List<T>::operator[](std::size_t index)
{
	return getNode(index)->value_;
}

template <typename T> inline 
const T& List<T>::operator[](std::size_t index) const
{
	return cgetNode(index)->value_;
}

template <typename T> inline std::size_t List<T>::size() const
{
	return numElements_;
}

template <typename T> inline bool List<T>::isEmpty() const
{
	return numElements_ == 0;
}

template <typename T> inline 
std::ostream& operator<<(std::ostream& str, const List<T>& list)
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
