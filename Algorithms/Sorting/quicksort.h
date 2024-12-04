#pragma once
#include <functional>
#include "../Random/random.h"
/// <summary>
/// Partitions the array in range [p:r]
/// Does not check if indexes p and r are within the array
/// Used as quicksort subroutine</summary>
/// <returns>Index of new pivot in subarray [p:r]</returns>
/// <param name="comp">Comparator to be used</param>
/// <returns>Index of array's pivot</returns>
template<class T, class Comparator = std::less<T>>
size_t partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	T& pivot = arr[r];
	size_t i = p;//highest index in the lowside
	for(size_t j = p;j<r;j++)
		if (comp(arr[j], pivot))//if the element belongs to lowside - swap it
			std::swap(arr[i++], arr[j]);

	std::swap(arr[i], arr[r]);
	return i;
}

/// <summary>
/// Partitions the array in range [p:r]
/// Does not check if indexes p and r are within the array
/// Returns pair of pivots q,t where elements within arr[q:t] are equal. This allows for effective partitioning of equal elements
/// Used as d_part_quicksort subroutine
/// </summary>
/// <returns>pivots q and t</returns>
template<class T, class Comparator = std::less<T>>
std::pair<size_t, size_t> double_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	T& pivot = arr[r];
	size_t i = p;//highest index in the lowside
	size_t ie = p;//highest index in the highside

	for (size_t j = p; j < r; j++)
	{
		if (arr[j] == pivot)
			std::swap(arr[ie++], arr[j]);

		else if (comp(arr[j], pivot))//if the element belongs to lowside - swap it
		{
			std::swap(arr[i++], arr[j]);//this basically moves [i:ie] by 1 position to right
			std::swap(arr[ie++], arr[j]);
		}
	}

	std::swap(arr[ie], arr[r]);
	return std::make_pair(i, ie);
}


/// <summary>
/// Original partitioning algorithm implemented by C.A.R Hoare
/// This algorithm should be more practical than usual partition algorithm, due to high possibility of making less swap calls
/// </summary>
/// <param name="comp">Comparator to be used</param>
/// <returns>Index of array's pivot</returns>
template<class T, class Comparator = std::less<T>>
size_t hoare_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	T& pivot = arr[p];
	long long i = p;
	long long j = r+1;
	while (true)
	{
		do {
			j--;
		} while (comp(arr[j], pivot));
		do {
			i++;
		} while (!comp(arr[i], pivot));

		if (i < j)
			std::swap(arr[i], arr[j]);
		else
			return j;
	}
}

/// <summary>
/// Partitions the array in range [p:r]
/// Pivot is chosen randomly
/// Does not check if indexes p and r are within the array
/// Used as randomized quicksort subroutine
/// </summary>
/// <param name="comp">Comparator to be used</param>
/// <returns>Index of array's pivot</returns>
template<class T, class Comparator = std::less<T>>
size_t random_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	size_t i = StaticRandom::NextLong(p, r + 1);
	std::swap(arr[r], arr[i]);//change pivot to random one
	return partition(arr, p, r);
}

/// <summary>
/// Partitions the array in range [p:r]
/// Pivot is chosen randomly from median of 3 random elements
/// Does not check if indexes p and r are within the array
/// </summary>
/// <returns>Index of array's pivot</returns>
template<class T, class Comparator = std::less<T>>
size_t random_median_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	if (r - p < 3)//return default partitioning if generating median of three is impossible
		return partition(arr, p, r, comp);

	size_t i = StaticRandom::NextLong(p, r - 2);
	T& median = std::max(std::min(arr[i], arr[i+1]), std::min(std::max(arr[i], arr[i+1]), arr[i+2]));
	std::swap(arr[r], median);
	return partition(arr, p, r);
}

template<class T, class Comparator = std::less<T>>
size_t median_of_3_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	if (r - p < 3)
		return hoare_partition(arr, p, r, comp);
	size_t middle = p + ((r - p) / 2);

	T& median = std::max(std::min(arr[p], arr[r]), std::min(std::max(arr[p], arr[r]), arr[middle]));
	std::swap(arr[r], median);
	return hoare_partition(arr, p, r, comp);
}

/*
	TODO: implement quickselect and implement median of medians algorithm
*/

/// <summary>
/// Quicksorts array in range [p:r]
/// p and r are not checked if they are withing array range
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator=std::less<T>>
void quicksort(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	if (p >= r || r ==size_t(0)-1) //size_t(0)-1 checks for size_t overflow
		return;

	size_t q = partition(arr, p, r, comp); //get array pivot
	quicksort(arr, p, q-1,comp);//quicksort lower side
	quicksort(arr, q+1, r,comp);//quicksort upper side
}

/// <summary>
/// Quicksorts array in range [p:r]
/// Uses tail-recursion elimination technique to maintain lg(n) stack deph 
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator=std::less<T>>
void tre_quicksort(T* arr, size_t p, size_t r, Comparator comp = Comparator())
{
	size_t q = 0;

	while (p < r && r != size_t(0) - 1) //size_t(0)-1 checks for size_t overflow
	{
		q = partition(arr, p, r, comp);

		if (q - p > r - q)//lower side is bigger
		{
			tre_quicksort(arr, p, q - 1, comp);//sort low side
			p = q + 1;
		}
		else //high side is bigger
		{
			tre_quicksort(arr, q+1, r, comp);//sort high side
			r = q - 1;
		}
	}
}

/// <summary>
/// Quicksorts array
/// Uses tail-recursion elimination technique to maintain lg(n) stack deph 
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator = std::less<T>>
void tre_quicksort(T* arr, const size_t& arr_size, Comparator comp = Comparator())
{
	tre_quicksort(arr,0, arr_size-1, comp);
}

/// <summary>
/// Quicksorts array in range [p:r] using random_partition subroutine
/// This version of quicksort yields better performance for large data sets
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator=std::less<T>>
void random_quicksort(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	if (p >= r || r == size_t(0) - 1) //size_t(0)-1 checks for size_t overflow
		return;

	size_t q = random_partition(arr, p, r, comp);
	random_quicksort(arr, p, q - 1, comp);
	random_quicksort(arr, q + 1, r, comp);
}

/// <summary>
/// Quicksorts given array
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator=std::less<T>>
void quicksort(T* arr, const size_t& arr_size, Comparator comp = Comparator())
{
	quicksort(arr, 0, arr_size - 1,comp);
}

/// <summary>
/// Quicksorts array using random_partition subroutine
/// This version of quicksort yields better performance for large data sets
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator=std::less<T>>
void random_quicksort(T* arr, const size_t& arr_size, Comparator comp = Comparator())
{
	random_quicksort(arr, 0, arr_size - 1, comp);
}

/// <summary>
/// Quicksorts array in range[p:r] using double_partition subroutine
/// This quicksort can sort arrays with equal elements, it also yields better performance for arrays with many equal elements
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator = std::less<T>>
void d_part_quicksort(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())
{
	if (p >= r || r == size_t(0) - 1) //size_t(0)-1 checks for size_t overflow
		return;

	auto pair = double_partition(arr,p, r,comp);
	random_quicksort(arr, p, pair.first-1, comp);
	random_quicksort(arr, pair.second + 1, r, comp);
}

/// <summary>
/// Quicksorts array using double_partition subroutine
/// This quicksort can sort arrays with equal elements, it also yields better performance for arrays with many equal elements
/// </summary>
/// <param name="comp">Comparator to be used, change comparator to change ordering</param>
template<class T, class Comparator = std::less<T>>
void d_part_quicksort(T* arr, const size_t& arr_size, Comparator comp = Comparator())
{
	d_part_quicksort(arr, 0, arr_size - 1, comp);
}