/*
 * @lc app=leetcode.cn id=59 lang=c
 *
 * [59] 螺旋矩阵 II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int** generateMatrix(int n, int* returnSize, int** returnColumnSizes)
{
    // 创建结果
    int** result = (int**)malloc(sizeof(int*) * n);
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    if (!result || !(*returnColumnSizes)) return NULL;

    (*returnSize) = n;

    for (int i = 0; i < n; i++)
    {
        (*returnColumnSizes)[i] = n;

        result[i] = (int*)malloc(sizeof(int) * n);
    }

    int up = 0, down = n - 1, left = 0, right = n - 1;
    int value = 1;

    int size = n * n;
    while (value <= size)
    {
        // 向右
        for (int i = left; i <= right && value <= size; i++)
        {
            result[up][i] = value++;
        }
        up++;

        // 向下
        for (int i = up; i <= down && value <= size; i++)
        {
            result[i][right] = value++;
        }
        right--;

        // 向左
        for (int i = right; i >= left && value <= size; i--)
        {
            result[down][i] = value++;
        }
        down--;

        // 向上
        for (int i = down; i >= up && value <= size; i--)
        {
            result[i][left] = value++;
        }
        left++;
    }

    return result;
}
// @lc code=end

