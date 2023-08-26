#pragma once
#include <functional>


//2.2-2
template<class T, class Comp = std::less<T>>
inline void selection_sort(T* arr, const int& size, Comp compare_function = Comp())
{
	int min_index = 0; //index of min element or whatever compare function does
	for (int x = 0; x < size-1; x++)
	{
		min_index = x;
		for (int y = x+1; y < size; y++)
		{
			if (compare_function(arr[y], arr[min_index]))
				min_index = y;
		}

		if(min_index!=x)
			std::swap(arr[x], arr[min_index]);
	}
}

/*
*  Worst case wariant : n^2
*  Best case wariant : n^2 (obviously it goes through the same steps)
*/
