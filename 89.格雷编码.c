/*
 * @lc app=leetcode.cn id=89 lang=c
 *
 * [89] ¸ñÀ×±àÂë
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

int* grayCode(int n, int* returnSize)
{
    if (n < 0)
    {
        (*returnSize) = 0;
        return NULL;
    }

    (*returnSize) = 1 << n;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    if (result == NULL)
    {
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < *returnSize; i++)
        result[i] = i ^ (i >> 1);

    return result;
}
// @lc code=end

