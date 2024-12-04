#pragma once
#include <iostream>
#include "columnsort.h"

void test_columnsort() {
    int matrix_static[6][3] = { {10,14,5},
    {8,7,17},
    {12,1,6},
    {16,9,11},
    {4,15,2},
    {18,3,13} };

    int** matrix = new int* [6];
    for (int x = 0; x < 6; x++)
        matrix[x] = new int[3];

    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 3; y++)
            matrix[x][y] = matrix_static[x][y];
    }

    std::cout << "Before sort:\n";
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 3; y++)
            std::cout << matrix[x][y] << "    ";
        std::cout << "\n";
    }

    columnsort(matrix, 3, 6);

    std::cout << "After sort:\n";
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 3; y++)
            std::cout << matrix[x][y] << "    ";
        std::cout << "\n";
    }

    for (int x = 0; x < 6; x++)
        delete[] matrix[x];
    delete[] matrix;
}