/*
 * @lc app=leetcode.cn id=54 lang=c
 *
 * [54] 螺旋矩阵
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize)
{
    if (!matrix || matrixSize == 0 || !matrixColSize || matrixColSize[0] == 0)
    {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int total = rows * cols;
    int* result = (int*)malloc(total * sizeof(int));
    *returnSize = total;

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int index = 0;

    while (index < total)
    {
        // 向右
        for (int col = left; col <= right && index < total; col++)
        {
            result[index++] = matrix[top][col];
        }
        top++;

        // 向下
        for (int row = top; row <= bottom && index < total; row++)
        {
            result[index++] = matrix[row][right];
        }
        right--;

        // 向左
        for (int col = right; col >= left && index < total; col--)
        {
            result[index++] = matrix[bottom][col];
        }
        bottom--;

        // 向上
        for (int row = bottom; row >= top && index < total; row--)
        {
            result[index++] = matrix[row][left];
        }
        left++;
    }

    return result;
}
// @lc code=end

