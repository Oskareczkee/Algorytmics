#pragma once
#include <functional>

/// <summary>
/// Heap implementation, has static methods to create heaps from arrays
/// This heap can be effectively used as priority queue
/// By default this is min-heap, change comparator to make it max-heap
/// </summary>
/// <typeparam name="Comparator">Comparator that will be used, change to std::greater to get max-heap</typeparam>
template<class T, class Comparator = std::less<T>>
class Heap
{
private:
	T* arr = nullptr;
	size_t size = 0;
	size_t capacity = 1;

	static size_t parent(const size_t& node) { return node >> 1; }
	static size_t left(const size_t& node)   { return  node << 1; }
	static size_t right(const size_t& node)  { return (node << 1) + 1; }


	T* get_array_copy(); //helper function to create a copy of array in heap
	void copy_array(T* arr, const size_t& size);//copies arr into heap arr, assumes that arr is already heap
	void delete_array();//deletes array

	void build_heap(T* arr, const size_t& size, Comparator comp = Comparator()); //build heap from array
	bool IsOk() { return size >= 0 && arr != nullptr; }//helper function that returns false if heap is not usable
	void resize();
public:
	Heap(){}
	Heap(const size_t& _capacity) : capacity(_capacity) {}
	Heap(T* arr, const size_t& arr_size) { build_heap(arr, arr_size); }
	Heap(const Heap& other);
	~Heap() { delete_array(); }

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

	/// <summary>
	/// Converts given array into heap
	/// </summary>
	static void array_heapify(T* arr, const size_t& size, Comparator comp = Comparator());
	/// <summary>
	/// Heapifies array on given node
	/// </summary>
	static void heapify(T* arr, const size_t& arr_size, const size_t& node, Comparator comp = Comparator());
};

template<class T, class Comparator>
void Heap<T, Comparator>::heapify(T* arr,const size_t& arr_size,const size_t& node, Comparator comp)
{
	size_t l = left(node);
	size_t r = right(node);

	size_t actual = node;
	size_t change = node;

	while (true)
	{
		if (l < arr_size && comp(arr[l], arr[actual]))
			change = l;
		else change = actual;
		if (r < arr_size && comp(arr[r], arr[change]))
			change = r;

		if (actual != change)
		{
			std::swap(arr[actual], arr[change]);
			actual = change;
			l = left(actual);
			r = right(actual);
		}
		else break;
	}
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::insert_arr(const T* arr, const size_t& arr_size, Comparator comp)
{
	if (!IsOk())
		return;

	for (size_t x = 0; x < arr_size; x++)
		insert(arr[x], comp);
}

template<class T, class Comparator>
void Heap<T, Comparator>::array_heapify(T* arr, const size_t& size, Comparator comp)
{
	//use long long, size_t is unsigned, so (size_t)0 - 1 = UINT64_MAX
	for (long long x = size >> 1; x >= 0; x--)
		heapify(arr, size, x,comp);
}

template<class T, class Comparator>
inline T* Heap<T, Comparator>::get_array_copy()
{
	T* out = new T[size];
	for (int x = 0; x < size; x++)
		out[x] = arr[x];
	return out;
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::copy_array(T* arr, const size_t& size)
{
	//delete previous array if existed
	delete_array();
	this->arr = new T[size];
	this->capacity = size;
	this->size = size;

	for (int x = 0; x < size; x++)
		this->arr[x] = arr[x];
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::delete_array()
{
	if (arr == nullptr)
		return;

	delete[] arr;
	size = 0;
	arr = nullptr;
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::build_heap(T* arr, const size_t& size, Comparator comp)
{
	delete_array();
	copy_array(arr, size);

	for (size_t x = size >> 1; x > 0; x--)
		heapify(this->arr,this->size,x, comp);
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::resize()
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

template<class T, class Comparator>
inline Heap<T, Comparator>::Heap(const Heap& other)
{
	//array in other heap is already heapified, so we need only to make a copy
	arr = new T[other.capacity];
	for (size_t x = 0; x < other.size; x++)
		arr[x] = other.arr[x];

	size = other.size;
	capacity = other.capacity;
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::pop()
{
	if (!IsOk())
		return;
	size--;
}

template<class T, class Comparator>
inline T Heap<T, Comparator>::top()
{
	if(!IsOk())
		return T();
	return arr[0];
}

template<class T, class Comparator>
inline T Heap<T, Comparator>::remove_top()
{
	if(!IsOk())
		return T();

	T top = top();
	std::swap(arr[0], arr[size - 1]); //swap top with last element, then pop it
	pop();
	heapify(arr, size, 0);
	return top;
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::remove(const T& val)
{
	if (!IsOk())
		return;

	size_t i = find(val);
	if (i < 0) //not found
		return;

	std::swap(arr[i], arr[size - 1]);
	pop();
	heapify(arr, size, i);
}

template<class T, class Comparator>
inline long long Heap<T, Comparator>::find(const T& val, Comparator comp)
{
	if (!IsOk())
		return -1;

	//simple linear search
	for (long long x = 0; x < size; x++)
		if (arr[x] == val)
			return x;

	return -1;
}

template<class T, class Comparator>
inline bool Heap<T, Comparator>::exists(const T& val)
{
	if (!IsOk())
		return false;

	return Find(val) >= 0;
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::change_value(const T& val, const T& new_val, Comparator comp)
{
	size_t i = Find(val);
	if (i < 0)
		return;

	arr[i] = new_val;

	while (i > 0 && !comp(arr[parent(i)], arr[i]))
	{
		std::swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
}

template<class T, class Comparator>
inline void Heap<T, Comparator>::insert(const T& val, Comparator comp)
{
	if (!IsOk())
		return;

	if (size == capacity)
		resize();

	size++;
	size_t i = size-1;
	arr[i] = val;

	//same as change value
	while (i > 0 && !comp(arr[parent(i)], arr[i]))
	{
		std::swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
}
