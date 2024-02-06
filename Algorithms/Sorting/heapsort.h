#pragma once
#include "Data Structures/Heap.h"

/// <summary>
/// Sorting algorithm using heap properties to sort data
/// </summary>
template<class T, class Comp = std::less<T>>
void heapsort(T* arr, const size_t& size, Comp comparator = Comp())
{
	Heap<T, Comp>::array_heapify(arr, size, comparator);
	size_t actual_size = size;
	for (size_t x = size-1; x >0; x--)
	{
		std::swap(arr[0], arr[x]);
		actual_size--;
		Heap<T, Comp>::heapify(arr, actual_size, 0,comparator);//heapify from root node
	}
}
