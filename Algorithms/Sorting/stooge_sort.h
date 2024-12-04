#pragma once
#include <functional>


/// <summary>
/// Sorts array in range [p:r] using stooge sort algorithm
/// Very bad sorting algorithm, even worse than bubble sort, but i does it job and sorts 
/// Do not use this algorithm for any real purposes
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator=std::less<T>>
void stooge_sort(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	if (!comp(arr[p], arr[r]))
		std::swap(arr[p], arr[r]);
	if (p + 1< r)
	{
		size_t k = (r - p +1) / 3;
		stooge_sort(arr, p, r - k,comp); //first 1/3
		stooge_sort(arr, p + k, r,comp); //second 2/3
		stooge_sort(arr, p, r - k,comp); //first 1/3
	}
}

/// <summary>
/// Sorts array using stooge sort algorithm
/// Very bad sorting algorithm, even worse than bubble sort, but i does it job and sorts things
/// Do not use this algorithm for any real purposes
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator = std::less<T>>
void stooge_sort(T* arr, const size_t& arr_size, Comparator comp = Comparator())
{
	stooge_sort(arr, 0, arr_size-1, comp);
}