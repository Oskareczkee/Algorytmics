#pragma once
#include <functional>
#include <math.h>

/*
* Merges the SORTED subarrays of arr array from A[p,q] to A[q+1,r]
* After operation A[p,r] subarray is sorted
* p,q,r are the endpoints of the subarrays to sort
*/
template<class T, class Comp>
inline void merge(T* arr, const int& p, const int& q, const int& r, Comp compare_function = Comp())
{
	int nl = q - p + 1; // length of A[p,q]
	int nr = r - q; // length of A[q + 1,r], do not add 1, since we use 0 indexing

	T* Left = new T[nl];
	T* Right = new T[nr];

	for (int i = 0; i < nl; i++) // copy A[p,q] into L[0, nl]
		Left[i] = arr[p + i];
	for (int i = 0; i < nr; i++) // copy A[q+1,r] into R[0, nr]
		Right[i] = arr[q + i + 1];

	int i = 0, j = 0; //indexes of the smallest element in Left array and Right array
	int k = p;// indexes of the current location in arr

	//As long as Left or Right contains unmerged elements, copy the smallest element into A[p,r]
	while (i < nl && j < nr)
	{
		if (compare_function(Left[i], Right[j]))
			arr[k++] = Left[i++];
		else
			arr[k++] = Right[j++];
	}

	//We went through the left or right entirely, that means that the remainder is sorted, we can just copy it at the end
	while (i < nl)
		arr[k++] = Left[i++];
	while (j < nr)
		arr[k++] = Right[j++];

	delete[] Left;
	delete[] Right;
}

template<class T, class Comp = std::less<T>>
inline void merge_sort(T* arr, const int& p, const int& r, Comp compare_function = Comp())
{
	if (p >= r) // one or zero element array
		return;

	int q = floor((p + r) / 2) ; // midpoint of A[p,r]
	merge_sort(arr, p, q, compare_function); // sort A[p,q]
	merge_sort(arr, q + 1, r, compare_function); // sort A[q+1,r]
	merge(arr, p, q, r, compare_function); //merge sorted subarrays into one
}

template<class T, class Comp = std::less<T>>
inline void merge_sort(T* arr, const int& size, Comp compare_function = Comp())
{
	//subtract one since we don't really need size, but the last index
	merge_sort(arr, 0, size-1, compare_function);
}