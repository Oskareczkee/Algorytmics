#pragma once

template<class T>
inline bool linear_search(T* arr, const size_t& size, const T& item)
{
	for (int x = 0; x < size; x++)
		if (arr[x] == item)
			return true;

	return false;
}
