#pragma once
#include <algorithm>

/// <summary>
/// Sorts array using counting sort
/// Counting sort first determines number of elements less or equal to x. Then using this information places x directly into into proper position
/// </summary>
/// <typeparam name="T">Counting sort can only sort integers do not change this parameter</typeparam>
/// <param name="arr">Array to sort</param>
/// <param name="arr_size">Size of the array to sort</param>
/// <param name="limit">maximum number in array, max(arr)</param>
template<class T=int>
void counting_sort(T* arr, const size_t& arr_size, const unsigned long long& limit) {
	T* counting_arr = new T[limit+1]; //+1, cause zero counts as well
	T* out = new T[arr_size];

	std::fill(counting_arr, counting_arr + limit+1, 0); //fill counting array with zeroes
	for (int x = 0; x < arr_size; x++)
		counting_arr[arr[x]]++; //C[x] now contains number of occurences of given number
	
	for (int x = 1; x <= limit; x++)
		counting_arr[x] += counting_arr[x - 1]; //C[x] now contains number of elements less than or equal to x

	for (int x = arr_size-1; x >= 0; x--)
	{
		out[counting_arr[arr[x]]-1] = arr[x]; //-1 to prevent indexing errors
		counting_arr[arr[x]]--; //this handles duplicate values, decrementing counter means that we have depleted 1 value
	}

	for (int x = 0; x < arr_size; x++)
		arr[x] = out[x]; //copy sorted array to original, i don't want to return new array, other sorts sort in place original array

	//delete garbage
	delete[] counting_arr;
	delete[] out;
}


/// <summary>
/// Sorts array using counting sort, automatically gets the max value in array
/// </summary>
/// <typeparam name="T">Counting sort can only sort integers do not change this parameter</typeparam>
/// <param name="arr">Array to sort</param>
/// <param name="arr_size">Size of the array to sort</param>
template<class T = int>
void counting_sort(T* arr, const size_t& arr_size) {
	counting_sort(arr, arr_size, *std::max_element(arr, arr + arr_size));
}