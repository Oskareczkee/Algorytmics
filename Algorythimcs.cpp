#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>

#include "Includes/include_sorting.h"
#include "Includes/include_numerical.h"
#include "Includes/include_random.h"
#include "Includes/include_data_structures.h"
#include "Utility/testing.h"
#include "order_statistics.h"

int main()
{
    int arr[] = { 6,19,4,12,14,9,15,7,8,11,3,13,2,5,10 };
    int rand_arr[20];
    std::iota(rand_arr, rand_arr + ARR_SIZE(rand_arr), 1);
    std::mt19937 rd;
    std::shuffle(rand_arr, rand_arr + ARR_SIZE(arr), std::mt19937(rd()));

    int out = select_ith(arr, ARR_SIZE(arr),5,5, std::greater<int>());
    std::cout << "Array: \n";
    print_array(arr, ARR_SIZE(arr));
    std::cout << "ith order element: " << out << "\n";
}


//TEST HEAP, YOUNG TABLEAU
/*
*   int arr[] = { 6,4,5,20,3,15,25,100};
    std::cout << "Array:\n";
    print_array(arr, ARR_SIZE(arr));
    D_AryHeap<int,3>::array_heapify(arr, ARR_SIZE(arr),3);
    //Heap<int>::array_heapify(arr, ARR_SIZE(arr));
    std::cout << "After using heap: \n";
    print_array(arr, ARR_SIZE(arr));
    heapsort<int>(arr, ARR_SIZE(arr));
    std::cout << "Heap sort array:\n";
    print_array(arr, ARR_SIZE(arr));

    D_AryHeap<int,3> heap(arr, ARR_SIZE(arr));
    std::cout << heap.get_size() << " " << heap.get_capacity() << "\n";
    heap.insert(2);
    std::cout << heap.find(6) << "\n";

    
    Heap<int> heap(arr, ARR_SIZE(arr));
    std::cout << heap.get_size() <<" "<< heap.get_capacity() << "\n";
    heap.insert(2);
    std::cout << heap.find(6) << "\n";

    young_tableau<int,std::greater<int>> tableau(4,4,INT32_MIN);
    int arr[] = { 9,16,3,2,4,8,5,14,12 };
    tableau.fill(arr, 9);
    tableau.insert(32);
    tableau.insert(1);
    tableau.extract_minmax();

    int** arrt = tableau.get_array();
    for (int x = 0; x < tableau.get_height(); x++)
    {
        for (int y = 0; y < tableau.get_width(); y++)
        {
            if (arrt[x][y] == INT32_MIN)
                std::cout << "-inf" << "\t";
            else
                std::cout << arrt[x][y] << "\t";
        }
        std::cout << "\n";
    }
*/

//TEST RANDOM ALGORITHMS
/*
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
*/

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
