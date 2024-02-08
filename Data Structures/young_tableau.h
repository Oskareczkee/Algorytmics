#pragma once
#include <functional>
#include "Data Structures/Heap.h"
#include "Algorithms/Sorting/merge_sort.h"

template<class T = int, class Comparator = std::less<T>>
class young_tableau
{
private:
	T** tableau=nullptr;
	size_t _width = 0, _height = 0, _size = 0;
	T infinity = T();

	void create_array();
	void delete_array();
	T** return_array_copy();
	void copy_array(T** arr, const size_t& width, const size_t& height);
	void fill_with_infinity();//fils tableau with infinity values
public:
	young_tableau(const T& infinity_val): infinity(infinity_val){}
	young_tableau(const size_t& width, const size_t& height, const T& infinity_val) : _width(width), _height(height), infinity(infinity_val) { create_array(); }
	young_tableau(const size_t& width, const size_t& height, const T& infinity_val,
		T* arr, const size_t& arr_size) : _width(width), _height(height), infinity(infinity_val){fill(arr, arr_size); }

	/// <summary>
	/// Fills young tableau with values from array, old values are replaced
	/// </summary>
	void fill(T* arr, const size_t arr_size, Comparator comp = Comparator());

	/// <summary>
	/// Inserts value into young tableau, does nothing if there is no space for new values
	/// </summary>
	void insert(const T& val, Comparator comp = Comparator());

	/// <summary>
	/// Inserts array of values into young tableau, does nothing if there is no space for new values
	/// </summary>
	void insert(T* arr, const size_t& arr_size, Comparator comp = Comparator());

	/// <summary>
	/// Gets minimal or maximal value (comparator defined)
	/// </summary>
	T minmax() { if (tableau == nullptr)return infinity; else return tableau[0][0]; }

	/// <summary>
	/// Gets minimal or maximal value (comparator defined) and deletes it from tableau, returns infinity if tableau does not exist
	/// </summary>
	T extract_minmax();

	/// <summary>
	/// Extracts value at given index in tableau and deletes it from tableau, returns infinity if arguments are inproper
	/// </summary>
	T extract(const size_t& x, const size_t& y, Comparator comp = Comparator());

	/// <summary>
	/// Returns true if young tableau is full, otherwise false
	/// </summary>
	bool is_full() { return tableau[_height - 1][_width - 1] != infinity || tableau == nullptr; }

	/// <summary>
	/// Sets infinity value to be used
	/// </summary>
	void set_infinity(const T& val) { infinity = val; }

	/// <summary>
	/// Adds number of rows and fills them with infinity values
	/// </summary>
	void add_rows(const int& count = 1);
	/// <summary>
	/// Adds number of columns and fills them with infinity values
	/// </summary>
	void add_cols(const int& count = 1);

	/// <summary>
	/// Changes size of tableau, fills empty fields with infinity values
	/// </summary>
	void change_size(const size_t& width, const size_t& height) { add_rows(_width - width); add_cols(_height - height); } //this can be done more efficently

	size_t get_width() { return _width; }
	size_t get_height() { return _height; }

	/// <summary>
	/// Returns copy of tableau, can return nullptr if tableau is not initialized
	/// </summary>
	T** get_array() {return return_array_copy();}
};

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::create_array()
{
	if (tableau != nullptr)
		delete_array();

	tableau = new T*[_height];
	for (size_t x = 0; x < _height; x++)
		tableau[x] = new T[_width];
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::delete_array()
{
	if (tableau == nullptr)
		return;

	for (int x = 0; x < _height; x++)
		delete[] tableau[x];
	delete[] tableau;

	tableau = nullptr;
}

template<class T, class Comparator>
inline T** young_tableau<T, Comparator>::return_array_copy()
{
	if (tableau == nullptr)
		return nullptr;

	T** out = new T*[_height];
	for (int x = 0; x < _height; x++)
	{
		out[x] = new T[_width];
		for (int y = 0; y < _width; y++)
			out[x][y] = tableau[x][y];
	}

	return out;
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::copy_array(T** arr, const size_t& width, const size_t& height)
{
	//inproper dimensions
	if (_width != width || _height != height)
		return;

	for (size_t x = 0; x < height; x++)
		for (size_t y = 0; y < width; y++)
			tableau[x][y] = arr[x][y];
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::fill_with_infinity()
{
	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _width; y++)
			tableau[x][y] = infinity;
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::fill(T* arr, const size_t arr_size, Comparator comp)
{
	merge_sort(arr, arr_size, comp);
	fill_with_infinity();

	for (int x = 0; x < _height; x++)
		for (int y = 0; y < _width; y++)
		{
			if (x * _width + y >= arr_size)
				break;
			tableau[x][y] = arr[x * _width + y];
		}
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::insert(const T& val, Comparator comp)
{
	//check if bottom is free
	if (is_full())
		return;

	tableau[_height - 1][_width - 1] = val;
	int actualx = _width - 1, actualy = _height - 1;//actual coordinates of value in table

	//move up and left to find proper place for value
	while (true)
	{
		if (actualy - 1>=0 && comp(val, tableau[actualy - 1][actualx]))
		{
			std::swap(tableau[actualy][actualx], tableau[actualy - 1][actualx]);
			actualy--;
			continue;
		}
		else if (actualx-1 >=0 && comp(val, tableau[actualy][actualx - 1]))
		{
			std::swap(tableau[actualy][actualx], tableau[actualy][actualx - 1]);
			actualx--;
			continue;
		}
		else
			break;
	}

}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::insert(T* arr, const size_t& arr_size, Comparator comp)
{
	for (size_t x = 0; x < arr_size; x++)
	{
		if (is_full())
			break;
		insert(arr[x], comp);
	}
}

template<class T, class Comparator>
inline T young_tableau<T, Comparator>::extract_minmax()
{
	if (tableau == nullptr)
		return infinity;

	return extract(0, 0);
}

template<class T, class Comparator>
inline T young_tableau<T, Comparator>::extract(const size_t& x, const size_t& y, Comparator comp)
{
	if (x >= _width || x < 0 || y >= _height || y < 0)
		return infinity;

	T val = tableau[x][y];
	tableau[y][x] = infinity;
	size_t actualx = x, actualy = y;

	//move up and left to find proper place for value
	while (true)
	{
		if (actualx + 1 < _width && !comp(tableau[actualy][actualx], tableau[actualy][actualx + 1]))
		{
			std::swap(tableau[actualy][actualx], tableau[actualy][actualx + 1]);
			actualx++;
			continue;
		}
		else if (actualy + 1 < _height && !comp(tableau[actualy][actualx], tableau[actualy + 1][actualx]))
		{
			std::swap(tableau[actualy][actualx], tableau[actualy + 1][actualx]);
			actualy++;
			continue;
		}
		else
			break;
	}

	return val;
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::add_rows(const int& count)
{
	if (_width + count < 0) //negative count values are allowed, this shrinks tableau
		return;

	T** copy = return_array_copy();
	size_t old_width = _width;
	delete_array();

	_width += count;

	tableau = new T*[_height];
	for (size_t x = 0; x < _height; x++)
		tableau[x] = new T[_width];

	fill_with_infinity();

	if (copy == nullptr)
		return;

	for (size_t x = 0; x < _height; x++)
		for (size_t y = 0; y < old_width && y < _width; y++)
			tableau[x][y] = copy[x][y];

	for (size_t x = 0; x < _height; x++)
		delete[] copy[x];
	delete[] copy;
}

template<class T, class Comparator>
inline void young_tableau<T, Comparator>::add_cols(const int& count)
{
	T** copy = return_array_copy();
	size_t old_height = _height;
	delete_array();

	_height += count;

	tableau = new T * [_height];
	for (size_t x = 0; x < _height; x++)
		tableau[x] = new T[_width];

	fill_with_infinity();

	if (copy == nullptr)
		return;

	for (size_t x = 0; x < old_height && x<_height; x++)
		for (size_t y = 0; y < _width; y++)
			tableau[x][y] = copy[x][y];

	for (size_t x = 0; x < old_height; x++)
		delete[] copy[x];
	delete[] copy;
}
