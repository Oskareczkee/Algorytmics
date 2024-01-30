#pragma once
#include <functional>
/// <summary>
/// Heap implementation using arrays. Implements min heap, change comparator to std::greater<T>, to change to max heap
/// </summary>
/// <typeparam name="T">Type to store in heap</typeparam>
/// <typeparam name="Comparator">Comparator to be used</typeparam>
template <class T, class Comparator = std::less<T>>
class Heap
{
private:
	const int INITIAL_SIZE = 1;
	const int OUT_OF_RANGE = -1;
	T* _arr;
	int _capacity;
	int _size;

	//HELPERS
	//gets left son of given node, returns OUT_OF_RANGE if does not exist
	int get_left(const int& node);
	//gets right son of given node, returns OUT_OF_RANGE if does not exist
	int get_right(const int& node);
	//gets parent of given node, returns OUT_OF_RANGE if does not exist
	int get_parent(const int& node);

	//resizes array, doubling its capacity
	void resize();
	//pops item at given index in array, helper function
	T pop(const int& index, Comparator comp = Comparator(),bool iAmDummyArgument=true);
public:

	Heap(): _capacity(INITIAL_SIZE), _size(0), _arr(new T[INITIAL_SIZE]){}
	Heap(const int& capacity);
	~Heap() { delete[] _arr; }

	//will add more if needed, this is basic implementation

	void push(const T& data, Comparator comp = Comparator());
	T pop(Comparator comp = Comparator());
	T pop(const T& elem, Comparator comp = Comparator());
	T* to_array(int& arr_size_ref) const;

	int size()const { return _size; }
	int capacity()const { return _capacity; }
};

template <class T, class Comparator>
inline Heap<T, Comparator>::Heap(const int& capacity): _size(0)
{
	capacity < 1 ? _capacity = 1 : _capacity = capacity;
	_arr = new T[_capacity];
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::push(const T& data, Comparator comp)
{
	if (_size == _capacity) //there is no space
		resize();

	_arr[_size] = data;
	_size++;
	int index = _size - 1;
	int parent = get_parent(index);

	while (parent != OUT_OF_RANGE)
	{
		//base case: data < _parent, other if comparator has been changed
		if (comp(data, _arr[parent]))
		{
			std::swap(_arr[parent], _arr[index]);
			index = parent;
			parent = get_parent(index);
		}
		else
			break;
	}
}

template<class T, class Comparator>
inline T Heap<T, Comparator>::pop(Comparator comp)
{
	return pop(0,comp, true);
}

template<class T, class Comparator>
inline T Heap<T, Comparator>::pop(const T& elem, Comparator comp)
{
	//find element in our array
	int elem_index = 0;
	bool found = false;
	for(int x =0;x<_size;x++)
		if (_arr[x] == elem)
		{
			elem_index = x;
			found = true;
			break;
		}

	if (!found)//if element was not found, return default
		return T();

	return pop(elem_index,comp, true);
}

template<class T, class Comparator>
inline T* Heap<T, Comparator>::to_array(int& arr_size_ref) const
{
	T* output = new T[_size];
	arr_size_ref = _size;
	//create copy of actual heap, not to change it
	Heap copy;
	for (int x = 0; x < _size; x++)
		copy.push(_arr[x]);

	//pop elemnets from copy to get ordered array
	for (int x = 0; x < _size; x++)
		output[x] = copy.pop();

	return output;
}


template <class T, class Comparator>
inline int Heap<T, Comparator>::get_left(const int& node)
{
	int index = node * 2 + 1;
	if (index < 0 || index > _size - 1)
		return OUT_OF_RANGE;

	return index;
}

template <class T, class Comparator>
inline int Heap<T, Comparator>::get_right(const int& node)
{
	int index = node * 2 + 2;
	if (index < 0 || index > _size - 1)
		return OUT_OF_RANGE;

	return index;
}

template <class T, class Comparator>
inline int Heap<T, Comparator>::get_parent(const int& node)
{
	if (node <= 0)
		return OUT_OF_RANGE;

	int index = (node - 1) / 2;
	if (index > _size - 1)
		return OUT_OF_RANGE;

	return index;
}

template <class T, class Comparator>
inline void Heap<T, Comparator>::resize()
{
	_capacity *= 2; //double the capacity

	T* temp = new T[_capacity];
	memcpy(temp, _arr, sizeof(T) * _size);

	delete[] _arr;
	_arr = temp; //temp becomes new arr
}

template<class T, class Comparator>
inline T Heap<T, Comparator>::pop(const int& index,Comparator comp, bool iAmDummyArgument)
{
	if (_size == 0 || index > _size -1 || index < 0)
		return T();

	T output = _arr[index];
	std::swap(_arr[index], _arr[_size - 1]);//swap this item with the last one
	_size--;


	int actual = index;
	int left = get_left(index);
	int right = get_right(index);
	int swap_index = 0; //index of node to swap

	while (left != OUT_OF_RANGE && right != OUT_OF_RANGE) //till our node is not leaf
	{
		if (right != OUT_OF_RANGE && comp(_arr[right], _arr[left]))
			swap_index = right;
		else
			swap_index = left;

			//heap condition is not satisified
			if (!comp(_arr[actual], _arr[swap_index]))
			{
				std::swap(_arr[actual], _arr[swap_index]);
					actual = swap_index;
					left = get_left(actual);
					right = get_right(actual);
			}
			else//condition is satisfied, we do not have to do anything
				break;
	}

	return output;
}