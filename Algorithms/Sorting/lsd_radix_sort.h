#pragma once
#include <algorithm>

/// <summary>
/// Sorts array of integers using radix sort. Please note that this algorithm cannot sort properly floating point numbers
/// </summary>
template<class T = int>
void radix_sort_int(T* arr, const size_t& arr_size) {
	T max = *std::max_element(arr, arr + arr_size);
	for (int exp = 1; max / exp > 0; exp *= 10)
		counting_sort_digit(arr, arr_size, exp);
}


/// <summary>
/// Sorts array using counting sort on given digit, given by exp (exp=1 -> 1st digit, exp=10 -> 2nd digit etc...)
/// This is used as sub routine for int sorting radix sort
/// Counting sort first determines number of elements less or equal to x. Then using this information places x directly into into proper position
/// </summary>
/// <typeparam name="T">Counting sort can only sort integers do not change this parameter</typeparam>
/// <param name="arr">Array to sort</param>
/// <param name="arr_size">Size of the array to sort</param>
/// <param name="limit">maximum number in array, max(arr)</param>
template<class T = int>
void counting_sort_digit(T* arr, const size_t& arr_size, const int& exp) {
	T* counting_arr = new T[10]; //there are 10 digits
	T* out = new T[arr_size];

	std::fill(counting_arr, counting_arr + 10, 0); //fill counting array with zeroes
	for (int x = 0; x < arr_size; x++)
		counting_arr[(arr[x]/exp)%10]++; //C[x] now contains number of occurences of given digit

	for (int x = 1; x < 10; x++)
		counting_arr[x] += counting_arr[x - 1]; //C[x] now contains number of elements less than or equal to x

	for (int x = arr_size - 1; x >= 0; x--)
	{
		out[counting_arr[(arr[x] / exp) % 10] - 1] = arr[x]; //-1 to prevent indexing errors
		counting_arr[(arr[x] / exp) % 10]--; //this handles duplicate values, decrementing counter means that we have depleted 1 value
	}

	for (int x = 0; x < arr_size; x++)
		arr[x] = out[x]; //copy sorted array to original, i don't want to return new array, other sorts sort in place original array

	//delete garbage
	delete[] counting_arr;
	delete[] out;
}