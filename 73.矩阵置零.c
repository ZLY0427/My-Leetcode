/*
 * @lc app=leetcode.cn id=73 lang=c
 *
 * [73] æÿ’Û÷√¡„
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize)
{
    if (!matrix || !matrixColSize || matrixSize <= 0 || matrixColSize[0] <= 0) return ;

    int maxSize = matrixSize * matrixColSize[0];
    int** isZero = (int**)malloc(sizeof(int*) * maxSize);
    if (!isZero) return ;
    for (int indexForMalloc = 0; indexForMalloc < maxSize; indexForMalloc++)
    {
        isZero[indexForMalloc] = (int*)malloc(sizeof(int) * 2);
        if (!isZero[indexForMalloc])
        {
            for (int indexForFree = 0; indexForFree < indexForMalloc; indexForFree++)
                free(isZero[indexForFree]);
            free(isZero);
            return ;
        }

        isZero[indexForMalloc][0] = isZero[indexForMalloc][1] = -1;
    }

    int nowSize = 0;
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixColSize[0]; j++)
        {
            if (matrix[i][j] == 0)
            {
                isZero[nowSize][0] = i;
                isZero[nowSize][1] = j;
                nowSize++;
            }
        }
    }

    for (int index = 0; index < nowSize; index++)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            matrix[i][isZero[index][1]] = 0;
        }
        for (int j = 0; j < matrixColSize[0]; j++)
        {
            matrix[isZero[index][0]][j] = 0;
        }
    }

    for (int indexForFree = 0; indexForFree < maxSize; indexForFree++)
        free(isZero[indexForFree]);
    free(isZero);
}
// @lc code=end

