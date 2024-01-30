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
#include "Algorithms/Random/propabilistic_counter.h"
#include "Algorithms/Random/array_permutations.h"
#include "Algorithms/Random/random.h"
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
    int arr[20];
    std::iota(arr, arr + ARR_SIZE(arr), 1);

    std::cout << "Random array:\n";
    print_array(arr, ARR_SIZE(arr));
    randomly_permute(arr, ARR_SIZE(arr));
    std::cout << "Random permutation:\n";
    print_array(arr, ARR_SIZE(arr));
    std::cout << "Permutation without identity:\n";
    permute_without_identity(arr, ARR_SIZE(arr));
    print_array(arr, ARR_SIZE(arr));
    std::cout << "Permute with all:\n";
    permute_with_all(arr, ARR_SIZE(arr));
    print_array(arr, ARR_SIZE(arr));
    std::cout << "Permute by cycle:\n";
    permute_by_cycle(arr, ARR_SIZE(arr));
    print_array(arr, ARR_SIZE(arr));

    std::cout << "Random sample:\n";
    int* arr2 = random_sample(arr, ARR_SIZE(arr), 5);
    print_array(arr2, 5);

    PropabilisticCounter counter;

    for (int x = 0; x < 100; x++)
        counter.Increment();

    std::cout << "Counter expected value: " << counter.Expected() << "\nCounter approximated value: " << counter.Approximation()<<"\n";

    delete[] arr2;
}

//TEST INVERSIONS
/*
int arr[] = { 8,4,2,1 };
//int arr[] = {1,20,6,4,5};
std::iota(arr, arr + ARR_SIZE(arr), 1);
std::mt19937 rd;
std::shuffle(arr, arr + ARR_SIZE(arr), std::mt19937(rd()));

std::cout << "Before sort:\n";
print_array(arr, ARR_SIZE(arr));

//sorting goes here
std::cout << "Inversions: " << count_inversions(arr, ARR_SIZE(arr)) << "\n";
std::cout << "Antyinversions: " << count_inversions(arr, ARR_SIZE(arr), std::greater<>()) << "\n";
auto invs = return_inversions(arr, ARR_SIZE(arr));
for (auto& inv : invs)
std::cout << "(" << inv.first << "," << inv.second << ")\n";

std::cout << "\n\nAfter sort:\n";
print_array(arr, ARR_SIZE(arr));
*/


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
