#pragma once
#include <vector>
#include <utility>
#include <iostream>

/*
* Merges the SORTED subarrays of arr array from A[p,q] to A[q+1,r]
* After operation A[p,r] subarray is sorted
* p,q,r are the endpoints of the subarrays to sort
* returns count of inversions or antyinversion of an array (change compare_function, to return antyinversions)
* Basically this is just copied merge sort
*/
template<class T, class Comp= std::less_equal<T>>
inline int merge_inversions(T* arr, const int& p, const int& q, const int& r, Comp compare_function = Comp())
{
	int inversions =0;
	int nl = q - p+1; // length of A[p,q]
	int nr = r - q; // length of A[q + 1,r], do not add 1, since we use 0 indexing

	T* Left = new T[nl];
	T* Right = new T[nr];

	for (int i = 0; i < nl; i++) // copy A[p,q] into L[0, nl]
		Left[i] = arr[p + i];
	for (int i = 0; i < nr; i++) // copy A[q+1,r] into R[0, nr]
		Right[i] = arr[q + i+1];

	int ip = p;//current real index from the left
	int i = 0, j = 0; //indexes of the smallest element in Left array and Right array
	int k = p;// indexes of the current location in arr

	//As long as Left or Right contains unmerged elements, copy the smallest element into A[p,r]
	while (i < nl && j < nr)
	{
		if (compare_function(Left[i], Right[j]))
		{
			arr[k++] = Left[i++];
			ip++;
		}
		else
		{
			arr[k++] = Right[j++];
			inversions+=(q-ip+1);
		}
	}

	//We went through the left or right entirely, that means that the remainder is sorted, we can just copy it at the end
	while (i < nl)
		arr[k++] = Left[i++];
	while (j < nr)
		arr[k++] = Right[j++];

	delete[] Left;
	delete[] Right;

	return inversions;
}

template<class T, class Comp = std::less_equal<T>>
inline int count_inversions(T* arr, const int& p, const int& r, Comp compare_function = Comp())
{
	int inversion_count=0;
	if (p<r)
	{
		int q = floor((p+r)/2); // midpoint of A[p,r]
		inversion_count+=count_inversions(arr, p, q, compare_function); // sort A[p,q]
		inversion_count+=count_inversions(arr, q+1, r, compare_function); // sort A[q+1,r]
		inversion_count+=merge_inversions(arr, p, q, r, compare_function); //merge sorted subarrays into one
	}

	return inversion_count;
}

/*
* returns count of inversions or antyinversions of an array (change compare_function, to return antyinversions)
* Basically this is just copied merge sort
*/
template<class T, class Comp = std::less_equal<T>>
inline int count_inversions(T* arr, const int& size, Comp compare_function = Comp())
{
	//create copy of array, that will be sorted, we do not want to change original array
	T* temp = new T[size];
	for (int x = 0; x < size; x++)
		temp[x] = arr[x];

	//subtract one since we don't really need size, but the last index
	int output = count_inversions(temp, 0, size-1, compare_function);
	delete[] temp;

	return output;
}

/*
	performs merge sort of an array and outputs count of its inversions or antyinversions
	choose proper compare_function to return antyinversions
*/
template<class T, class Comp = std::less_equal<T>>
inline int merge_sort_and_count_inversions(T* arr, const int& size, Comp compare_function = Comp())
{
	//subtract one since we don't really need size, but the last index
	return count_inversions(arr, 0, size-1, compare_function);
}

/*
	Counts inversions using iterative approach, slower than standard count_inversions
	Instead uses less memory, iterations are also faster than recurrence for small inputs
	comparator std::less - inversions
			   std::greater - antyinversions
*/
template<class T, class Comp = std::less_equal<T>>
inline int count_inversions_iter(T* arr, const int& size, Comp compare_function = Comp())
{
	int inversions =0;

	for(int x =0;x<size;x++)
		for(int y=x+1;y<size;y++)
			if(!compare_function(arr[x], arr[y]))
				inversions++;

	return inversions;
}

/*
	Counts inversions using iterative approach, slower than standard count_inversions
	Instead uses less memory, iterations are also faster than recurrence for small inputs
	Returns vector which contains all inversions
	comparator std::less - inversions
			   std::greater - antyinversions
*/
template<class T, class Comp = std::less<T>>
inline std::vector<std::pair<T,T>> return_inversions_iter(T* arr, const int& size, Comp compare_function = Comp())
{
	std::vector<std::pair<T,T>> inversions;

	for(int x =0;x<size;x++)
		for(int y=x+1;y<size;y++)
			if(!compare_function(arr[x], arr[y]))
				inversions.push_back(std::pair(arr[x], arr[y]));

	return inversions;
}


template<class T, class Comp = std::less_equal<T>>
inline void return_inversions(T* arr, const int& p, const int& q, const int& r, 
							  std::vector<std::pair<T,T>>& inversions, 
							  Comp compare_function = Comp())
{
	int nl = q - p + 1; // length of A[p,q]
	int nr = r - q; // length of A[q + 1,r], do not add 1, since we use 0 indexing

	T* Left = new T[nl];
	T* Right = new T[nr];

	for (int i = 0; i < nl; i++) // copy A[p,q] into L[0, nl]
		Left[i] = arr[p + i];
	for (int i = 0; i < nr; i++) // copy A[q+1,r] into R[0, nr]
		Right[i] = arr[q + i + 1];

	int ip = p;//current real index from the left
	int i = 0, j = 0; //indexes of the smallest element in Left array and Right array
	int k = p;// indexes of the current location in arr

	//As long as Left or Right contains unmerged elements, copy the smallest element into A[p,r]
	while (i < nl && j < nr)
	{
		if (compare_function(Left[i], Right[j]))
		{
			arr[k++] = Left[i++];
			ip++;
		}
		else
        {
			for(int x=1;x<=(q-ip+1);x++)// if left is > right, then the rest of the values to the right, are inversions as well
				inversions.push_back(std::pair<T,T>(arr[k], arr[k+x]));
			arr[k++] = Right[j++];
        }
	}

	//We went through the left or right entirely, that means that the remainder is sorted, we can just copy it at the end
	while (i < nl)
		arr[k++] = Left[i++];
	while (j < nr)
		arr[k++] = Right[j++];

	delete[] Left;
	delete[] Right;
}

template<class T, class Comp = std::less_equal<T>>
inline void return_inversions(T* arr, const int& p, const int& r,
							  std::vector<std::pair<T,T>>& inversions, 
							  Comp compare_function = Comp())
{
	if (p >= r) // one or zero element array
		return;

	int q = (p + r) / 2 ; // midpoint of A[p,r]
	return_inversions(arr, p, q, inversions, compare_function); // sort A[p,q]
	return_inversions(arr, q + 1, r, inversions, compare_function); // sort A[q+1,r]
	return_inversions(arr, p, q, r, inversions, compare_function); //merge sorted subarrays into one
}

/*
* returns count of inversions or antyinversions of an array (change compare_function, to return antyinversions)
* Basically this is just copied merge sort
*/
template<class T, class Comp = std::less_equal<T>>
inline std::vector<std::pair<T,T>> return_inversions(T* arr, const int& size, Comp compare_function = Comp())
{
	//create copy of array, that will be sorted, we do not want to change original array
	T* temp = new T[size];
	for (int x = 0; x < size; x++)
		temp[x] = arr[x];

	std::vector<std::pair<T,T>> output;

	//subtract one since we don't really need size, but the last index
	return_inversions(temp, 0, size-1, output, compare_function);
	delete[] temp;

	return output;
}




