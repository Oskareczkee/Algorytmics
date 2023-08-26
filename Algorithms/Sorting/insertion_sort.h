#pragma once
#include <algorithm>


template<class T, class Comp = std::less<T>>
inline void insertion_sort(T* arr, const int& size, Comp compare_function = Comp())
{
	for (int i = 1; i < size; i++)
	{
		T key = arr[i];
		int j = i - 1;

		while (j >= 0 && compare_function(key, arr[j]))
		{
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = key;
	}
}