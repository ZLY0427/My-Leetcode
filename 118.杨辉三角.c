/*
 * @lc app=leetcode.cn id=118 lang=c
 *
 * [118] Ñî»ÔÈý½Ç
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int** generate(int numRows, int* returnSize, int** returnColumnSizes)
{
    if (numRows <= 0) return NULL;

    *returnSize = numRows;
    
    int** result = (int**)malloc(sizeof(int*) * numRows);
    if (!result) return NULL;

    *returnColumnSizes = (int*)malloc(sizeof(int) * numRows);
    for (int i = 0; i < numRows; ++i)
    {
        (*returnColumnSizes)[i] = i + 1;
        result[i] = (int*)malloc(sizeof(int) * (i + 1));
        if (!result[i])
        {
            for (int j = 0; j < i; ++j) free(result[j]);
            free(result);
            return NULL;
        }

        result[i][0] = 1;
        result[i][i] = 1;
    }

    for (int i = 2; i < numRows; ++i)
        for (int j = 1; j < i; ++j)
            result[i][j] = result[i - 1][j - 1] + result[i - 1][j];

    return result;
}
// @lc code=end

