/*
 * @lc app=leetcode.cn id=48 lang=c
 *
 * [48] Ðý×ªÍ¼Ïñ
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

void swap(int* num1, int* num2);

void rotate(int** matrix, int matrixSize, int* matrixColSize)
{
    if (!matrix || matrixSize <= 1) return;

    int size = matrixSize;

    bool (*is_rotate)[size] = calloc(size * size, sizeof(bool));

    for (int indexLen = 0; indexLen < size / 2; indexLen++)
    {
        for (int indexRow = 0; indexRow < (size + 1) / 2; indexRow++)
        {
            if (is_rotate[indexLen][indexRow] == false)
            {
                swap(&matrix[indexLen][indexRow], &matrix[size - 1 - indexRow][indexLen]);
                swap(&matrix[size - 1 - indexRow][indexLen], &matrix[size - 1 - indexLen][size - 1 - indexRow]);
                swap(&matrix[size - 1 - indexLen][size - 1 - indexRow], &matrix[indexRow][size - 1 - indexLen]);
                is_rotate[indexLen][indexRow] = is_rotate[size - 1 - indexRow][indexLen] =
                is_rotate[size - 1 - indexLen][size - 1 - indexRow] = is_rotate[indexRow][size - 1 - indexLen] =\
                true;
            }
        }
    }
}

void swap(int* num1, int* num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
// @lc code=end

