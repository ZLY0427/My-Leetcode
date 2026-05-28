/*
 * @lc app=leetcode.cn id=119 lang=c
 *
 * [119] Ñî»ÔÈý½Ç II
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* getRow(int rowIndex, int* returnSize)
{
    if (rowIndex < 0) return NULL;

    *returnSize = rowIndex + 1;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    if (!result) return NULL;

    for (int i = 0; i < *returnSize; i++)
    {
        result[i] = 1;
        for (int j = i - 1; j > 0; j--) result[j] += result[j - 1];
    }

    return result;
}
// @lc code=end

