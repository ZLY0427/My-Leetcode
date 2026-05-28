/*
 * @lc app=leetcode.cn id=39 lang=c
 *
 * [39] 组合总和
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b);
void backtrack(int* candidates, int candidatesSize, int target, 
               int* path, int pathSize, int currentSum, int start, 
               int*** result, int* returnSize, int** col_sizes);

int** combinationSum(int* candidates, int candidatesSize, int target, 
                     int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (candidatesSize == 0)
    {
        *returnColumnSizes = NULL;
        return NULL;
    }

    qsort(candidates, candidatesSize, sizeof(int), compare);

    int** result = NULL;
    *returnColumnSizes = NULL;

    int* path = (int*)malloc(sizeof(int) * target);

    backtrack(candidates, candidatesSize, target, path, 0, 0, 0, 
              &result, returnSize, returnColumnSizes);

    free(path);
    return result;
}

int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void backtrack(int* candidates, int candidatesSize, int target, 
               int* path, int pathSize, int currentSum, int start, 
               int*** result, int* returnSize, int** col_sizes) {
    if (currentSum == target)
    {
        int* newpath = (int*)malloc(sizeof(int) * pathSize);
        memcpy(newpath, path, sizeof(int) * pathSize);

        (*result) = (int**)realloc(*result, sizeof(int*) * (*returnSize + 1));
        (*result)[*returnSize] = newpath;
        
        *col_sizes = (int*)realloc(*col_sizes, sizeof(int) * (*returnSize + 1));
        (*col_sizes)[*returnSize] = pathSize;

        (*returnSize)++;
        return;
    }

    if (currentSum > target)
    {
        return;
    }

    for (int i = start; i < candidatesSize; i++)
    {
        int num = candidates[i];
        if (currentSum + num > target) break;

        path[pathSize] = num;
        backtrack(candidates, candidatesSize, target, path, pathSize + 1,
                  currentSum + num, i, result, returnSize, col_sizes);
    }
}
// @lc code=end

