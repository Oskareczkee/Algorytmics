#pragma once
#include <math.h>

template<class T>
inline bool binary_search_desc(T* arr, const size_t& size, const T& item)
{
	int p = 0, q = 0, r = size; // begin, middle, end of actual subarray
	q = floor(size / 2); // middle of the array

	while (p <= r)
	{
		if (item == arr[q])
			return true;
		if (item < arr[q]) // if the item is on the left of the array
			r = q -1;
		else
			p = q +1;
		q = p + (r-p)/2;
	}

	return false;
}

template<class T>
inline bool binary_search_asc(T* arr, const size_t& size, const T& item)
{
	int p = 0, q = 0, r = size; // begin, middle, end of actual subarray
	q = floor(size / 2); // middle of the array

	while (p <= r)
	{
		if (item == arr[q])
			return true;
		if (item > arr[q]) // if the item is on the left of the array
			r = q - 1;
		else
			p = q + 1;
		q = p + (r - p) / 2;
	}

	return false;
}


/*
* In binary search algorithm initial array has to be sorted
* This implementation evokes proper function for ascending and descdening arrays
*/
template<class T>
inline bool binary_search(T* arr, const size_t& size, const T& item)
{
	//1 item or invalid array properties cases
	if (size == 1 && arr[0] == item)
		return true;
	else if (size < 1)
		return false;

	if (arr[0] < arr[1])
		return binary_search_desc(arr, size, item);
	else
		return binary_search_asc(arr, size, item);
}


/*
* In binary search algorithm initial array has to be sorted
* In recursive approach you need to specify beginning and end of the array
* p,r - begin and end index of searched array
* No implementation for descending functions is provided
*/
template<class T>
inline bool binary_search_recursive(T* arr, int p, int r, const T& item)
{
	int q = floor((p+r) / 2); // middle of the array

	while (p <= r)
	{
		if (item == arr[q])
			return true;
		if (item < arr[q]) // if the item is on the left of the array
			return binary_search_recursive(arr, p, r = q -1, item);
		else
			return binary_search_recursive(arr, p = q +1, r, item);
	}

	return false;
}