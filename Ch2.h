#pragma once
#include <bitset>

//2.1.2
inline double sum_array(double* arr, const size_t& size)
{
	double sum = 0;
	for (int x = 0; x < size; x++)
		sum += arr[x];

	return sum;
}

/*
*  Average case: n/2 - element may be somewhere in the middle
*  Worst case: n - element is not present
*/

/*
* 2.3-2
* test p!=r will work for n>=1, cause the smallest value for r will be 1, and the test will pass for 1 element array
* Test won't pass for n < 1, cause someone may have inserted negative n or 0
*/
