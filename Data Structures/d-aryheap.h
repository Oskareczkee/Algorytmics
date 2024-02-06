#pragma once
#include <functional>

//diarrhea heap

/// <summary>
/// D-AryHeap implementation
/// D-AryHeap is a heap, in which each parent has n children, i call it base
/// </summary>
/// <typeparam name="base">Number of children per parent</typeparam>
template<class T,int base=2, class Comparator = std::less<T>>
class D_AryHeap
{
private:
	T* arr=nullptr;
	size_t size = 0;
	size_t capacity = 0;


	/// <summary>
	/// Gets parent of given node in base n d-ary heap
	/// </summary>
	/// <param name="base">Base of the heap</param>
	/// <returns>Parent of given node</returns>
	static size_t parent(const size_t& node, const int& base) { return node/base; }
	/// <summary>
	/// Gets nth child of given node in base n d-ary heap
	/// </summary>
	/// <param name="nth">Number of child node</param>
	/// <param name="base">Base of the heap</param>
	/// <returns>nth child of parent</returns>
	static size_t child(const size_t& node, const size_t& nth, const int& base) { return  (node*base) + nth; }

	T* get_array_copy(); //helper function to create a copy of array in heap
	void copy_array(T* arr, const size_t& size);//copies arr into heap arr, assumes that arr is already heap
	void delete_array();//deletes array

	void build_heap(T* arr, const size_t& size, Comparator comp = Comparator()); //build heap from array
	bool IsOk() { return size >= 0 && arr != nullptr && base>=2; }//helper function that returns false if heap is not usable
	static bool IsOk(T* arr,const size_t& arr_size, const int& base) { return arr_size > 0 && base >= 2 && arr!=nullptr; }//helper function for checking argument of static functions
	void resize();
public:
	/// <summary>
	/// Converts given array into base n d-ary heap
	/// </summary>
	/// <param name="base">Base of output heap</param>
	static void array_heapify(T* arr, const size_t& size, const int& base, Comparator comp = Comparator());
	/// <summary>
	/// Heapifies given array on given node to base n d-ary heap
	/// </summary>
	/// <param name="base">Base of heap</param>
	static void heapify(T* arr, const size_t& arr_size, const size_t& node, const int& base, Comparator comp = Comparator());

	/// <summary>
	/// Returns min/max child (comparator defined) of given array
	/// Array must be proper base n d-ary heap
	/// </summary>
	/// <param name="base">Base of the heap</param>
	/// <returns>Index of min/max child, if node has no children, returns node</returns>
	static size_t get_min_child(T* arr, const size_t& arr_size, const size_t& node, const int& base, Comparator comp = Comparator());

	D_AryHeap(){}
	D_AryHeap(const size_t& _capacity) : capacity(_capacity) {}
	D_AryHeap(T* arr, const size_t& arr_size) { build_heap(arr, arr_size); }
	D_AryHeap(const D_AryHeap& other);
	~D_AryHeap() { delete_array(); }

	size_t get_size() { return size; }
	size_t get_capacity() { return capacity; }

	/// <summary>
	/// pops the last element
	/// </summary>
	void pop();
	/// <summary>
	/// Gets the top element, returns default value if top does not exist
	/// </summary>
	T top();
	/// <summary>
	/// Gets the top element and deletes it, returns default value if top does not exist
	/// </summary>
	T remove_top();

	/// <summary>
	/// Removes given element from heap, if not found nothing happens
	/// </summary>
	void remove(const T& val);

	/// <summary>
	/// Finds given value in heap's array and returns its index
	/// If item cannot be found value < 0 is returned
	/// </summary>
	long long find(const T& val, Comparator comp = Comparator());
	/// <summary>
	/// Finds given value in heap, returns true if exists, false if not
	/// </summary>
	bool exists(const T& val);

	/// <summary>
	/// Changes given value in the heap to the new one, if it exists
	/// </summary>
	void change_value(const T& val, const T& new_val, Comparator comp = Comparator());

	/// <summary>
	/// Inserts value into heap
	/// </summary>
	void insert(const T& val, Comparator comp = Comparator());

	/// <summary>
	/// Inserts array of values into heap
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="comp"></param>
	void insert_arr(const T* arr, const size_t& arr_size, Comparator comp = Comparator());
};

template<class T, int base, class Comparator>
inline size_t D_AryHeap<T, base, Comparator>::get_min_child(T* arr, const size_t& arr_size, const size_t& node, const int& base, Comparator comp)
{
	if (!IsOk(arr, arr_size, base))
		return node;

	size_t min_child = child(node,0,base);
	if (min_child >= arr_size)
		return node;

	size_t actual_child = 0;

	for (int x = 1; x < base; x++)
	{
		actual_child = child(node, x, base);
		if (actual_child >= arr_size)
			break;

		if (comp(arr[actual_child], arr[min_child]))
			min_child = actual_child;
	}

	return min_child;
}

template<class T, int base, class Comparator>
inline D_AryHeap<T, base, Comparator>::D_AryHeap(const D_AryHeap& other)
{
	//array in other heap is already heapified, so we need only to make a copy
	arr = new T[other.capacity];
	for (size_t x = 0; x < other.size; x++)
		arr[x] = other.arr[x];

	size = other.size;
	capacity = other.capacity;
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::pop()
{
	if (!IsOk())
		return;
	size--;
}

template<class T, int base, class Comparator>
inline T D_AryHeap<T, base, Comparator>::top()
{
	if(!IsOk())
		return T();
	return arr[0];
}

template<class T, int base, class Comparator>
inline T D_AryHeap<T, base, Comparator>::remove_top()
{
	if (!IsOk())
		return T();

	T top = top();
	std::swap(arr[0], arr[size - 1]); //swap top with last element, then pop it
	pop();
	heapify(arr, size, 0,base);
	return top;
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::remove(const T& val)
{
	if (!IsOk())
		return;

	size_t i = find(val);
	if (i < 0) //value has not been found
		return;

	std::swap(arr[i], arr[size - 1]);
	pop();
	heapify(arr, size, i,base);
}

template<class T, int base, class Comparator>
inline long long D_AryHeap<T, base, Comparator>::find(const T& val, Comparator comp)
{
	if (!IsOk())
		return -1;

	//simple linear search
	for (long long x = 0; x < size; x++)
		if (arr[x] == val)
			return x;

	return -1;
}

template<class T, int base, class Comparator>
inline bool D_AryHeap<T, base, Comparator>::exists(const T& val)
{
	if (!IsOk())
		return false;

	return find(val) >= 0;
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::change_value(const T& val, const T& new_val, Comparator comp)
{
	size_t i = Find(val);
	if (i < 0)
		return;

	arr[i] = new_val;

	while (i > 0 && !comp(arr[parent(i,base)], arr[i]))
	{
		std::swap(arr[i], arr[parent(i,base)]);
		i = parent(i,base);
	}
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::insert(const T& val, Comparator comp)
{
	if (!IsOk())
		return;

	if (size == capacity)
		resize();

	size++;
	size_t i = size - 1;
	arr[i] = val;

	//same as change value
	while (i > 0 && !comp(arr[parent(i,base)], arr[i]))
	{
		std::swap(arr[i], arr[parent(i,base)]);
		i = parent(i,base);
	}
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::insert_arr(const T* arr, const size_t& arr_size, Comparator comp)
{
	if (!IsOk())
		return;

	for (size_t x = 0; x < arr_size; x++)
		insert(arr[x], comp);
}

template<class T, int base, class Comparator>
inline T* D_AryHeap<T, base, Comparator>::get_array_copy()
{
	T* out = new T[size];
	for (size_t x = 0; x < size; x++)
		out[x] = arr[x];
	return out;
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::copy_array(T* arr, const size_t& size)
{
	//delete previous array if existed
	delete_array();
	this->arr = new T[size];
	this->capacity = size;
	this->size = size;

	for (int x = 0; x < size; x++)
		this->arr[x] = arr[x];
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::delete_array()
{
	if (arr == nullptr)
		return;

	delete[] arr;
	size = 0;
	arr = nullptr;
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::build_heap(T* arr, const size_t& size, Comparator comp)
{
	delete_array();
	copy_array(arr, size);

	for (size_t x = size/base; x > 0; x--)
		heapify(this->arr, this->size, x,base, comp);
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::resize()
{
	capacity *= 2;
	T* arr = get_array_copy();
	size_t old_size = size;
	delete_array();

	this->size = old_size;
	this->arr = new T[capacity];

	for (size_t x = 0; x < size; x++)
		this->arr[x] = arr[x];

	delete[] arr;
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::array_heapify(T* arr, const size_t& size, const int& base, Comparator comp)
{
	//use long long, size_t is unsigned, so (size_t)0 - 1 = UINT64_MAX
	for (long long x = size/base; x >= 0; x--)
		heapify(arr, size, x,base, comp);
}

template<class T, int base, class Comparator>
inline void D_AryHeap<T, base, Comparator>::heapify(T* arr, const size_t& arr_size, const size_t& node, const int& base, Comparator comp)
{
	if (!IsOk(arr, arr_size, base))
		return;

	size_t actual = node;
	size_t change = node;

	while (true)
	{
		change = get_min_child(arr, arr_size, actual, base, comp);

		if (actual != change)
		{
			std::swap(arr[actual], arr[change]);
			actual = change;
		}
		else 
			break;
	}
}
