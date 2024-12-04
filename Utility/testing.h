#pragma once
#include <iostream>

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

template <class T>
void print_array(T* arr, const size_t& size, std::ostream& os = std::cout)
{
    os << "{ ";
    for (int x = 0; x < size; x++)
        os << arr[x] << " ";
    os << " }\n";
}