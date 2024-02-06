#pragma once
#include <functional>

template<class T = int, class Comparator = std::less<T>>
class young_tableaux
{
private:
	T** tableau=nullptr;
	size_t _width = 0, _height = 0, _size = 0;

	void create_array();
	void delete_array();
	T** return_array_copy();
	void copy_array(T** arr, const size_t& width, const size_t& height);
public:
	young_tableaux(){}
	young_tableaux(const size_t& width, const size_t& height) : _width(width), _height(height) { create_array() };

};

template<class T, class Comparator>
inline void young_tableaux<T, Comparator>::create_array()
{
	if (tableau != nullptr)
		delete_array();

	tableau = new T*[_height];
	for (size_t x = 0; x < _height; x++)
		tableau[x] = new T[_width];
}

template<class T, class Comparator>
inline void young_tableaux<T, Comparator>::delete_array()
{
	if (tableau == nullptr)
		return;

	for (int x = 0; x < _height; x++)
		delete[] tableau[x];
	delete[] tableau;

	tableau = nullptr;
}

template<class T, class Comparator>
inline T** young_tableaux<T, Comparator>::return_array_copy()
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
inline void young_tableaux<T, Comparator>::copy_array(T** arr, const size_t& width, const size_t& height)
{
	//inproper dimensions
	if (_width != width || _height != height)
		return;

	for (size_t x = 0; x < height; x++)
		for (size_t y = 0; y < width; y++)
			tableau[x][y] = arr[x][y];
}
