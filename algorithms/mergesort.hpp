/**
 * \file mergesort.hpp
 * \author Dan Obermiller
 * \remarks Interface of the mergesort algorithm
 */

#ifndef MERGESORT_HPP
#define MERGESORT_HPP 1

#include <algorithm>
#include <cstddef>


template <typename T>
void _mergesort(T* array, const std::size_t size);

template <typename T>
void _split(T* arr1, const std::size_t start, const std::size_t end, T* arr2);

template <typename T>
void _merge(
	T* arr1, const std::size_t start, const std::size_t middle, 
	const std::size_t end, T* arr2);

/**
 * \brief An in place merge sort implementation.
 */
template <typename T, template <typename T> class I> inline
void mergesort(I<T>& iterable) 
{

}

/**
 * \brief An in place merge sort implementation.
 */
template <typename T> inline
void mergesort(T* array, const std::size_t size)
{
	_mergesort(array, size);
}

/**
 * \brief A copying merge sort implementation.
 * \post The initial iterable is unchanged.
 */
template <typename T, template <typename T> class I> inline
void mergesort(I<T> const& iterable, I<T>& newIterable)
{

}

/**
 * \brief A copying merge sort implementation.
 * \post The initial array is unchanged.
 */
template <typename T> inline
void mergesort(T const* array, const std::size_t size, T* newArray)
{
	std::copy(array, array + size, newArray);

	_mergesort(array, size);

	delete [] newArray;
}

/**
 * \brief The underlying merge sort function.  All of the above are simply
 *        convenience wrappers for this function.
 */
template <typename T> inline
void _mergesort(T* array, const std::size_t size)
{
	T* arr2 = new T[size];
	_split(array, 0, size, arr2);
}

/**
 * \brief Splits an array.
 * \remarks The range here is [start, end) - end is exclusive, start is not.
 */
template <typename T> inline
void _split(T* arr1, const std::size_t start, const std::size_t end, T* arr2)
{
	// We only have a length one array left to sort.
	if (end - start < 2)
		return;

	std::size_t middle = (end + start) / 2;
	_split(arr1, start, middle, arr2);
	_split(arr1, middle, end, arr2);
	_merge(arr1, start, middle, end, arr2);
	std::copy(arr2 + start, arr2 + end, arr1 + start);
}

/**
 * \brief Performs the actual merge.
 */
template <typename T> inline
void _merge(
	T* arr1, const std::size_t start, const std::size_t middle, 
	const std::size_t end, T* arr2)
{
	std::size_t i0 = start;
	std::size_t i1 = middle;

	for (std::size_t j = start; j < end; ++j) {
		if (i0 < middle && (i1 >= end || arr1[i0] <= arr1[i1])) {
			arr2[j] = arr1[i0];
			++i0;
		} else {
			arr2[j] = arr1[i1];
			++i1;
		}
	}
}

#endif
