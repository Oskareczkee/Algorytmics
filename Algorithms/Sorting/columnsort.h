#pragma once
#include <stdexcept>
#include <functional>
#include "Algorithms/Sorting/quicksort.h"

template<class T>
void columnsort_sort_columns(T** matrix, const size_t& row_size, const size_t& column_size) {
	//sort each column	
	T* column = new T[column_size]; //instead of deleting and creating create once and reuse
	for (int x = 0; x < row_size; x++) {

		for (int y = 0; y < column_size; y++)
			column[y] = matrix[y][x];

		quicksort(column, column_size);
		for (int y = 0; y < column_size; y++) //put sorted column into its place
			matrix[y][x] = column[y];
	}
	//clean memory!
	delete[] column;
}

/// <summary>
/// Transposes the matrix, but keeps its shape. In other words it turns leftmost column into the top r/s rows in order and so on
/// </summary>
template<class T>
void columnsort_transpose_noreshape(T** matrix, const size_t& row_size, const size_t& column_size) {
	T** copy = new T * [column_size];
	for (int x = 0; x < column_size; x++)
		copy[x] = new T[row_size];

	size_t copy_column = 0;
	size_t copy_row = 0;

	//transpose
	for (int x = 0; x < row_size; x++) {
		for (int y = 0; y < column_size; y++) {
			copy[copy_column][copy_row++] = matrix[y][x];

			if (copy_row == row_size) {
				copy_row = 0;
				copy_column++;
			}
		}
	}

	//copy the copy into original matrix
	for (int x = 0; x < column_size; x++)
		for (int y = 0; y < row_size; y++)
			matrix[x][y] = copy[x][y];

	//clean memory!
	for (int x = 0; x < column_size; x++)
		delete[] copy[x];

	delete[] copy;
}

/// <summary>
/// Inverses of the transposition of the matrix, but keeps its shape. In other words it turns top row into the leftmost s/r column in order and so on
/// </summary>
template<class T>
void columnsort_inverse_transpose_noreshape(T** matrix, const size_t& row_size, const size_t& column_size) {
	T** copy = new T * [column_size];
	for (int x = 0; x < column_size; x++)
		copy[x] = new T[row_size];

	size_t copy_column = 0;
	size_t copy_row = 0;

	//transpose
	for (int x = 0; x < column_size; x++) {
		for (int y = 0; y < row_size; y++) {
			copy[copy_column++][copy_row] = matrix[x][y];

			if (copy_column == column_size) {
				copy_column = 0;
				copy_row++;
			}
		}
	}

	//copy the copy into original matrix
	for (int x = 0; x < column_size; x++)
		for (int y = 0; y < row_size; y++)
			matrix[x][y] = copy[x][y];

	//clean memory!
	for (int x = 0; x < column_size; x++)
		delete[] copy[x];
	delete[] copy;
}

template<class T>
void columnsort_shift_columns(T** matrix, const size_t& row_size, const size_t& column_size) {
	T** copy = new T * [column_size];
	for (int x = 0; x < column_size; x++)
		copy[x] = new T[row_size + 1];//additional column is needed

	size_t column_half = column_size / 2;

	//shift top half of each column to bottom half of each column
	for (int x = 0; x < row_size; x++)
		for (int y = 0; y < column_half; y++)
			copy[y + column_half][x] = matrix[y][x];

	//shift the bottom half of each column into the top half of next column
	for (int x = 0; x < row_size; x++)
		for (int y = 0; y < column_half; y++)
			copy[y][x + 1] = matrix[y + column_half][x];

	//sort left bottom half
	T* lb_cpy = new T[column_half];
	for (int x = 0; x < column_half; x++)
		lb_cpy[x] = copy[x + column_half][0];

	quicksort(lb_cpy, column_half);
	for (int x = 0; x < column_half; x++)
		copy[x + column_half][0] = lb_cpy[x];

	//sort right top half
	for (int x = 0; x < column_half; x++)
		lb_cpy[x] = copy[x][row_size];
	quicksort(lb_cpy, column_half);
	for (int x = 0; x < column_half; x++)
		copy[x][row_size] = lb_cpy[x];

	delete[] lb_cpy;

	//sort the rest of the columns
	T* column_data = new T[column_size];//create once and delete once
	for (size_t x = 1; x < row_size; x++) {
		for (size_t y = 0; y < column_size; y++) {
			column_data[y] = copy[y][x];
		}

		quicksort(column_data, column_size);

		// Put the sorted data back into the `copy` matrix
		for (size_t y = 0; y < column_size; y++)
			copy[y][x] = column_data[y];
	}
	delete[] column_data;

	//perform the inverse of previous permutation
	//shift bottom half of each column to top half of each column
	for (int x = 0; x < row_size; x++)
		for (int y = 0; y < column_half; y++)
			matrix[y][x] = copy[y + column_half][x];

	//shift the top half of each column into the bottom half of next column
	for (int x = row_size - 1; x > 0; x--) //x>0 instead of x>=0 because we have x-1 operation
		for (int y = 0; y < column_half; y++)
			matrix[y + column_half][x - 1] = copy[y][x];

	//clean memory!
	for (int x = 0; x < column_size; x++)
		delete[] copy[x];
	delete[] copy;
}

/// <summary>
/// <para>Sorts rectangular array of n elements in column-major order. Given matrix has to be rectangular array</para>
/// <para>In order to work row_size must be even, column_size must be divisor of row_size, r>=s^2 (last restriction is not checked)</para>
/// </summary>
/// <param name="matrix">matrix to sort</param>
/// <param name="row_size">row size of matrix</param>
/// <param name="column_size">column size of matrix</param>
template<class T>
void columnsort(T** matrix, const size_t& row_size, const size_t& column_size) {
	if (column_size % 2 != 0 || column_size % row_size != 0/* || row_size < (2 * (column_size * column_size))*/) //last requirement can be violated sometimes, so i do not check it now
		throw std::invalid_argument("Wrong size of input matrix. Check requirements of input matrix"); //wrong input, do not sort

	columnsort_sort_columns(matrix, row_size, column_size);	//sort each column
	columnsort_transpose_noreshape(matrix, row_size, column_size); //do this weird transposition
	columnsort_sort_columns(matrix, row_size, column_size); //sort each column
	columnsort_inverse_transpose_noreshape(matrix, row_size, column_size); //do inverse of this werid transposition
	columnsort_sort_columns(matrix, row_size, column_size); //sort each column
	columnsort_shift_columns(matrix, row_size, column_size); //TODO: test this shit
}