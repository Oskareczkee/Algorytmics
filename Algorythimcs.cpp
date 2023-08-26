#include <iostream>
#include <algorithm>
#include "Algorithms/Sorting/insertion_sort.h"
#include "Algorithms/Sorting/selection_sort.h"
#include "Algorithms/Sorting/merge_sort.h"
#include "Algorithms/Searching/binary_search.h"
#include "Algorithms/Searching/linear_search.h"
#include "Ch2.h"

#define ARR_SIZE(arr) sizeof(arr) / sizeof(nums[0])

template<class T>
void print_array(T* arr, const size_t& size, std::ostream& os = std::cout)
{
    os << "{ ";
    for (int x = 0; x < size; x++)
        os << arr[x] << " ";
    os << " }\n";
}

int main()
{
    int nums[] = { 22,6,3,30,21,4 };

    insertion_sort(nums, ARR_SIZE(nums));
    std::cout << "Insertion sort:\n";
    print_array(nums, sizeof(nums) / sizeof(nums[0]));
    
    std::random_shuffle(nums, nums + ARR_SIZE(nums));
    selection_sort(nums, ARR_SIZE(nums));
    std::cout << "Selection sort:\n";
    print_array(nums, ARR_SIZE(nums));

    std::random_shuffle(nums, nums + ARR_SIZE(nums));

    merge_sort(nums,ARR_SIZE(nums));
    std::cout << "Merge sort: \n";
    print_array(nums, ARR_SIZE(nums));

    


    if (linear_search(nums, 6, 22))
        std::cout << "Linear Search Number found\n";
    else
        std::cout << "Linear Search Number not found\n";

    if (binary_search_recursive(nums,0, ARR_SIZE(nums), 312))
        std::cout << "Binary Search Number found\n";
    else
        std::cout << "Binary Search Number not found\n";
}
