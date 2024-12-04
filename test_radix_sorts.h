#pragma once
#include <iostream>
#include <random>
#include <numeric>
#include "Utility/testing.h"
#include "Algorithms/Sorting/counting_sort.h"
#include "Algorithms/Sorting/lsd_radix_sort.h"
#include "Algorithms/Sorting/msd_radix_sort.h"


void test_radix_sorts() {
    int arr[20];
    std::string arr_str[] = {
        "apple",
        "banana",
        "grape",
        "kiwi",
        "orange",
        "strawberry",
        "blueberry",
        "peach",
        "pear",
        "plum",
        "pineapple",
        "mango",
        "watermelon",
        "fig",
        "papaya"
    };
    std::iota(arr, arr + ARR_SIZE(arr), 1);
    std::mt19937 rd;
    std::shuffle(arr, arr + ARR_SIZE(arr), std::mt19937(rd()));
    std::shuffle(arr_str, arr_str + ARR_SIZE(arr_str), std::mt19937(rd()));

    std::cout << "Before sort:\n";
    print_array(arr, ARR_SIZE(arr));
    print_array(arr_str, ARR_SIZE(arr_str));
    //sorting goes here
    counting_sort(arr, ARR_SIZE(arr), *std::max_element(arr, arr + ARR_SIZE(arr)));
    msd_radix_sort_string(arr_str, ARR_SIZE(arr_str));


    std::cout << "\n\nAfter sort:\n";
    print_array(arr, ARR_SIZE(arr));
    std::cout << "\n";
    print_array(arr_str, ARR_SIZE(arr_str));
}