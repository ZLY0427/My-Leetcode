/*
 * @lc app=leetcode.cn id=74 lang=c
 *
 * [74] ËÑË÷¶þÎ¬¾ØÕó
 */

// @lc code=start
#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixSize,
                  int* matrixColSize, int target)
{
    if (!matrix || !matrixColSize || matrixSize <= 0 || matrixColSize[0] <= 0) return false;

    int left = 0, right = matrixColSize[0] - 1;
    int index = 0;

    while (index < matrixSize)
    {
        if (matrix[index][left] <= target && target <= matrix[index][right]) break;
        index++;
    }

    if (index == matrixSize) return false;

    while (left <= right)
    {
        int middle = (right + left) / 2;
        if (matrix[index][middle] == target) return true;
        else if (matrix[index][middle] < target) left = middle + 1;
        else right = middle - 1;
    }

    return false;
}
// @lc code=end

