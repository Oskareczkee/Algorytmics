#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>

#include "Algorithms/Sorting/insertion_sort.h"
#include "Algorithms/Sorting/selection_sort.h"
#include "Algorithms/Sorting/merge_sort.h"
#include "Algorithms/Searching/binary_search.h"
#include "Algorithms/Searching/linear_search.h"
#include "Algorithms/Sorting/bubble_sort.h"
#include "Algorithms/Numerical/Horner.h"
#include "Algorithms/Numerical/array_inversion.h"
#include "Data Structures/Heap.h"

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

template <class T>
void print_array(T *arr, const size_t &size, std::ostream &os = std::cout)
{
    os << "{ ";
    for (int x = 0; x < size; x++)
        os << arr[x] << " ";
    os << " }\n";
}

int main()
{
    int arr[] = {1,20,6,4,5};
   /*
   std::iota(arr, arr + ARR_SIZE(arr), 1);
   std::mt19937 rd;
   std::shuffle(arr, arr + ARR_SIZE(arr), std::mt19937(rd()));
   */

   std::cout<<"Before sort:\n";
   print_array(arr, ARR_SIZE(arr));

   //sorting goes here
   std::cout<<"Inversions: "<<count_inversions(arr, ARR_SIZE(arr))<<"\n";
   //std::cout<<"Antyinversions: "<<count_inversions(arr, ARR_SIZE(arr), std::greater<>())<<"\n";

   std::cout<<"\n\nAfter sort:\n";
   print_array(arr, ARR_SIZE(arr));
}

// TEST SORTING ALGORITHMS
/*
   int arr[20];
   std::iota(arr, arr + ARR_SIZE(arr), 1);
   std::mt19937 rd;
   std::shuffle(arr, arr + ARR_SIZE(arr), std::mt19937(rd()));

   std::cout<<"Before sort:\n";
   print_array(arr, ARR_SIZE(arr));

   //sorting goes here

   std::cout<<"\n\nAfter sort:\n";
   print_array(arr, ARR_SIZE(arr));
*/
