/**
 * \file mergesort.hpp
 * \author Dan Obermiller
 * \remarks Interface of the mergesort algorithm
 */

#ifndef MERGESORT_HPP
#define MERGESORT_HPP 1

#include <cstddef>

/**
 * \brief An in place merge sort implementation.
 * \remarks Does allocate and initialize a temporary array for the sorting.
 */
template <typename T, template <typename T> class I>
void mergesort(I<T>& iterable);

/**
 * \brief An in place merge sort implementation.
 * \remarks, Again, allocates and initializes an intermediate array.
 */
template <typename T>
void mergesort(T* array, std::size_t size);

/**
 * \brief A copying merge sort implementation.
 * \post The initial iterable is unchanged.
 */
template <typename T, template <typename T> class I>
void mergesort(const I<T>& iterable, I<T>& newIterable);

/**
 * \brief A copying merge sort implementation.
 * \post The initial array is unchanged.
 */
template <typename T>
void mergesort(const T* array, std::size_t size, T* newArray);

#endif
