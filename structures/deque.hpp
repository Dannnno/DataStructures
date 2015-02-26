/**
 * \file deque.hpp
 * \author Dan Obermiller
 * \brief Implementation of a doubly list.
 * \remarks Uses templates and operator overloading to provide an almost
 * enjoyable interface.
 */

#ifndef D_LINKEDLIST_HPP
#define D_LINKEDLIST_HPP 1

#include <cstddef>
#include <string>
#include <iostream>

#include "../exceptions.hpp"


template <typename T>
class Deque;

/**
 * \brief Overloading the << operator to allow clean string 
 *        representations of the deque.
 */
template <typename T> 
std::ostream& operator<<(std::ostream& str, const Deque<T>& list);


template <typename T>
/**
 * \brief A paramaterized doubly linked list
 */
class Deque
{
public:

	/**
	 * \brief A default constructor for a deque.
	 */
	Deque();

	/**
	 * \brief A constructor from an array.
	 */
	Deque(T* arr, std::size_t length);

	/**
	 * \brief The destructor.
	 */
	~Deque();

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
	 * \brief Adds a node to the start of a list.
	 */
	void appendLeft(T value);

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
	 * \brief inserts an item at the indicated index.
	 */
	void insert(std::size_t index, T value);

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
	template <typename TYPE> struct Node 
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


template <typename T> inline Deque<T>::Deque() :
	numElements_(0), head_(nullptr), tail_(nullptr) {
}

template <typename T> inline Deque<T>::Deque(
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

template <typename T> inline Deque<T>::~Deque()
{
	Node<T>* current = head_;
	Node<T>* next = nullptr;
	while (current != nullptr) {
		next = current->next_;
		delete current;
		current = next;
	}
}

template <typename T> inline T& Deque<T>::getHead()
{
	return head_->value_;
}

template <typename T> inline T& Deque<T>::getTail()
{
	return tail_->value_;
}

template <typename T> inline 
void Deque<T>::append(T node)
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
void Deque<T>::appendLeft(T node)
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
void Deque<T>::remove()
{
	if (numElements_ == 0)
		throw IndexOutOfBoundsException(0, std::string("Deque"));

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
void Deque<T>::remove(std::size_t n)
{
	if (n >= numElements_) 
		throw IndexOutOfBoundsException(n, std::string("Deque"));

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
T Deque<T>::pop()
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
		throw IndexOutOfBoundsException(0, std::string("Deque"));
	
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
		throw IndexOutOfBoundsException(n, std::string("Deque"));

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
void Deque<T>::insert(std::size_t n, T value)
{
	if (n > numElements_)
		throw IndexOutOfBoundsException(n, std::string("Deque"));

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
T& Deque<T>::operator[](std::size_t index)
{
	return getNode(index)->value_;
}

template <typename T> inline 
const T& Deque<T>::operator[](std::size_t index) const
{
	return cgetNode(index)->value_;
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
std::ostream& operator<<(std::ostream& str, const Deque<T>& list)
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
