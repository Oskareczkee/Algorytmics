#pragma once
#include "random.h"

//randomly permutes given array
template<class T>
void randomly_permute(T* arr, const size_t& size)
{
	for (int x = 0; x < size; x++)
		std::swap(arr[x], arr[StaticRandom::Next(x, size)]);
}

//randomly permutes given array, without identity permutations et. permutation that is original array
template<class T>
void permute_without_identity(T* arr, const size_t& size)
{
	for (int x = 0; x < size; x++)
		std::swap(arr[x], arr[StaticRandom::Next(x + 1, size)]);
}

//randomly permutes given array, swapping every element with a random element in range [0, size). Does not produce uniform random permutations
template<class T>
void permute_with_all(T* arr, const size_t& size)
{
	for (int x = 0; x < size; x++)
		std::swap(arr[x], arr[StaticRandom::Next(0, size)]);
}

//randomly permutes given array, using cycling, produced permutation is uniformly random
template<class T>
void permute_by_cycle(T* arr, const size_t& size)
{
	T* copy = new T[size];
	for (int x = 0; x < size; x++)
		copy[x] = arr[x];

	int offset = StaticRandom::Next(0, size);

	//cycling
	for (int x = 0; x < size; x++)
	{
		int dest = x + offset;
		if (dest >= size)
			dest = dest - size;

		copy[dest] = arr[x];
	}

	//copy
	for (int x = 0; x < size; x++)
		arr[x] = copy[x];

	delete[] copy; //free memory
}

//creates and returns new array of size = size, with random permutation of arr, if size > arr_size returns nullptr
template<class T>
T* random_sample(T* arr, const size_t& arr_size, const size_t& size)
{
	if (size > arr_size)
		return nullptr;

	T* copy = new T[arr_size]; //create copy, and permute it
	T* output = new T[size];
	for (int x = 0; x < arr_size; x++)
		copy[x] = arr[x];

	randomly_permute(copy, arr_size);
	for (int x = 0; x < size; x++)
		output[x] = copy[x];

	delete[] copy;
	return output;
}

