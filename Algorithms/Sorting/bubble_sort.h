#pragma once
#include <algorithm>

template <class T, class Comp= std::less<T>>
inline void bubble_sort(T* arr, const int& size, Comp compare_function = Comp())
{
    for(int x =0;x<size;x++)
    {
        for(int y=size-1; y>x;y--)
            if(compare_function(arr[y], arr[y-1]))
                std::swap(arr[y], arr[y-1]);
    }
}