#pragma once
#include <stdexcept>
#include "Algorithms/Random/random.h"
#include "Algorithms/Sorting/quicksort.h"

/// <summary>
/// Partitions the array in range [p:r].
/// Does not check if indexes p and r are within the array.
/// Used as randomized select subroutine</summary>
/// <returns>Index of new pivot in subarray [p:r]</returns>
/// <param name="comp">Comparator to be used</param>
/// <returns>Index of array's pivot</returns>
template<class T, class Comparator = std::less<T>>
size_t order_stats_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator()) //name has been changed to omit confilicts with sorting partitioning
{
	T& pivot = arr[r];
	size_t i = p;//highest index in the lowside
	for (size_t j = p; j < r; j++)
		if (comp(arr[j], pivot))//if the element belongs to lowside - swap it
			std::swap(arr[i++], arr[j]);

	std::swap(arr[i], arr[r]);
	return i;
}

/// <summary>
/// Partitions the array in range [p:r]
/// Pivot is chosen randomly
/// Does not check if indexes p and r are within the array
/// Used as randomized select subroutine
/// </summary>
/// <param name="comp">Comparator to be used</param>
/// <returns>Index of array's pivot</returns>
template<class T, class Comparator = std::less<T>>
size_t order_stats_randomized_partition(T* arr, const size_t& p, const size_t& r, Comparator comp = Comparator())//name has been changed to omit confilicts with sorting partitioning
{
	size_t i = StaticRandom::NextLong(p, r + 1);
	std::swap(arr[r], arr[i]);//change pivot to random one
	return order_stats_partition(arr, p, r, comp);
}

/// <summary>
/// Finds minimal element (1st order statistic) in the array
/// </summary>
template<class T>
T miniumum(T* arr, const size_t& arr_size) {
	if (arr == nullptr) throw std::invalid_argument("Array cannot be nullptr");

	T min = arr[0];
	for (int x = 1; x < arr_size; x++)
		if (arr[x] < min)
			min = arr[x];

	return min;
}


/// <summary>
/// Finds maximal element (nth order statistic) in the array
/// </summary>
template<class T>
T maximum(T* arr, const size_t& arr_size) {
	if (arr == nullptr) throw std::invalid_argument("Array cannot be nullptr");

	T max = arr[0];
	for (int x = 1; x < arr_size; x++)
		if (arr[x] > max)
			max = arr[x];

	return max;
}

/// <summary>
/// Finds minimal and maximal element (1st and nth order statistic) in the array
/// </summary>
/// <returns>Pair where first -> minimum, second -> maximum</returns>
template<class T>
std::pair<T, T>minmax(T* arr, const size_t& arr_size) {
	if (arr == nullptr) throw std::invalid_argument("Array cannot be nullptr");

	T max = arr[0];
	T min = arr[0];
	for (int x = 1; x < arr_size; x++) {
		if (arr[x] > max)
			max = arr[x];
		if (arr[x] < min)
			min = arr[x];
	}

	return std::make_pair(min, max);
}

/// <summary>
/// Randomized select algorithm is quicksort like subroutine to find nth order statistic
/// This version uses randomized_partition instead of normal one
/// This is used as a main subroutine of ith_order function
/// </summary>
/// <param name="comp">Comparator to be used, std::less can be used to find ith smallest element, std::greater to find ith greatest element</param>
/// <param name="p">left side index</param>
/// <param name="r">right side index</param>
/// <param name="i">number of order statistic i=1 -> minimum, i=arr_size -> maximum</param>
/// <returns>ith order element</returns>
template<class T, class Comparator = std::less<T>>
T randomized_select(T* arr, const size_t& p, const size_t& r, const unsigned int& i, Comparator comp = Comparator()) {
	if (p == r)
		return arr[p];

	size_t q = order_stats_randomized_partition(arr, p, r, comp); //partition the array and get the pivot
	size_t k = q - p + 1;

	if (i == k)
		return arr[q];
	else if (i < k)
		return randomized_select(arr, p, q - 1, i);
	else
		return randomized_select(arr, q + 1, r, i - k);

}

/// <summary>
/// Same as <see cref="randomized_select"/> but instead of using recursion it uses loop for iteration
/// </summary>
/// <param name="comp">Comparator to be used, std::less can be used to find ith smallest element, std::greater to find ith greatest element</param>
/// <param name="p">left side index</param>
/// <param name="r">right side index</param>
/// <param name="i">number of order statistic i=1 -> minimum, i=arr_size -> maximum</param>
/// <returns>ith order element</returns>
template<class T, class Comparator = std::less<T>>
T randomized_select_iter(T* arr, size_t p, size_t r, int i, Comparator comp = Comparator()) {
	while (p != r) {
		size_t q = order_stats_randomized_partition(arr, p, r, comp); //partition the array and get the pivot
		size_t k = q - p + 1;

		if (i == k)
			return arr[q];
		else if (i < k)
			r = q - 1;
		else {
			p = q + 1;
			i -= k;
		}
	}

	return arr[p];
}

/// <summary>
/// Returns ith order statistic using recursive randomized select algorithm
/// </summary>
/// <param name="comp">Comparator to be used, std::less can be used to find ith smallest element, std::greater to find ith greatest element</param>
/// <param name="i">number of order statistic i=1 -> minimum, i=arr_size -> maximum</param>
/// <returns>ith order element</returns>
template<class T, class Comparator = std::less<T>>
T ith_order_recursive(T* arr, const size_t& arr_size, const unsigned int& i, Comparator comp = Comparator()) {
	T* arr_cpy = new T[arr_size];
	std::copy(arr, arr + arr_size, arr_cpy); //work on copy, otherwise array item order will get changed

	T out = randomized_select(arr_cpy, 0, arr_size - 1, i, comp);
	delete[] arr_cpy;
	return out;
}

/// <summary>
/// Returns ith order statistic using randomized select algorithm
/// </summary>
/// <param name="comp">Comparator to be used, std::less can be used to find ith smallest element, std::greater to find ith greatest element</param>
/// <param name="i">number of order statistic i=1 -> minimum, i=arr_size -> maximum</param>
/// <returns>ith order element</returns>
template<class T, class Comparator = std::less<T>>
T ith_order(T* arr, const size_t& arr_size, const unsigned int& i, Comparator comp = Comparator()) {
	T* arr_cpy = new T[arr_size];
	std::copy(arr, arr + arr_size, arr_cpy); //work on copy, otherwise array item order will get changed

	T out = randomized_select_iter(arr_cpy, 0, arr_size - 1, i, comp);
	delete[] arr_cpy;
	return out;
}

template<class T, class Comparator = std::less<T>>
size_t order_stats_partition_around(T* arr, const size_t& p, const size_t& r, const size_t& pv, Comparator comp = Comparator()) {

	std::swap(arr[r], arr[pv]); //swap pivot so it becomes partition element

	//everything else here is usual partition code
	T& pivot = arr[r];
	size_t i = p;//highest index in the lowside
	for (size_t j = p; j < r; j++)
		if (comp(arr[j], pivot))//if the element belongs to lowside - swap it
			std::swap(arr[i++], arr[j]);

	std::swap(arr[i], arr[r]);
	return i;
}

/// <summary>
/// Selects ith order element using median of median algorithm
/// </summary>
/// <param name="p">Left side of array</param>
/// <param name="r">Right side of array</param>
/// <param name="th">Ith order element to find</param>
/// <param name="comp">Comparator to be used, std::less can be used to find ith smallest element, std::greater to find ith greatest element</param>
/// <param name="number_of_medians">number of medians to calculate in median of medians algorithm. This number must be odd and greater than 3</param>
/// <returns>Ith order element</returns>
template<class T, class Comparator = std::less<T>>
T select(T* arr, size_t p, size_t r, unsigned int i, const unsigned int& median_count, Comparator comp = Comparator()) {
	while ((r - p+1) % median_count != 0) { //this loop also handles the case when arr_size > median_count
		for (size_t j = p + 1; j <= r; j++) { //put minimum into arr[p]
			if (comp(arr[j], arr[p]))
				std::swap(arr[p], arr[j]);
		}

		if (i == 1)	return arr[p]; //if we want minimum we are done

		p++; //otherwise get (i-1)st element from arr[p+1:r]
		i--;
	}
	size_t g = (r - p + 1) / median_count; //number of median_count element groups

	for (size_t j = p, count=0; j < p + g - 1; j++,count++) //sort each group, group medians now lie in the middle of each group
		quicksort(arr + j + count*median_count, median_count, comp);

	//median of medians will lie in the middle group
	size_t select_lower = median_count / 2;
	size_t select_high = select_lower + 1;

	size_t x = select(arr, p + select_lower * g, p + select_high * g - 1, ceil(g / 2.0), median_count, comp); //find pivot x recursively as median of group medians
	size_t q = order_stats_partition_around(arr, p, r, x, comp); //partition around median of group medians
	size_t k = q - p + 1;

	if (i == k)
		return arr[q];
	else if (i < k)
		return select(arr, p, q - 1, i, median_count,comp);
	else
		return select(arr, q + 1, r, i - k, median_count,comp);
}

/// <summary>
/// Selects ith order element using median of median algorithm
/// </summary>
/// <param name="th">Ith order element to find</param>
/// <param name="comp">Comparator to be used, std::less can be used to find ith smallest element, std::greater to find ith greatest element</param>
/// <param name="number_of_medians">number of medians to calculate in median of medians algorithm. This number must be odd and greater than 3</param>
/// <returns>Ith order element</returns>
template<class T, class Comparator = std::less<T>>
T select_ith(T* arr, const size_t& arr_size, const unsigned int& ith, const unsigned int& number_of_medians=5, Comparator comp = Comparator()) {

	if (number_of_medians % 2 == 0) throw std::invalid_argument("numbers of medians in algorithm has to be odd number");
	else if (number_of_medians < 3) throw std::invalid_argument("numbers of medians in algorithm has to be greater or equal 3");

	T* arr_cpy = new T[arr_size];
	std::copy(arr, arr + arr_size, arr_cpy);

	T out = select(arr_cpy, 0, arr_size-1, ith, number_of_medians,comp);
	delete[] arr_cpy;
	return out;
}

