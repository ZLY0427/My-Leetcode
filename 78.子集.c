/*
 * @lc app=leetcode.cn id=78 lang=c
 *
 * [78] 子集
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int getSize(int num);
void back(int* nums, int numsSize, int indexNums,
          int* path, int indexPath,
          int** result, int* index, int** resultColumnSizes);

int** subsets(int* nums, int numsSize,
              int* returnSize, int** returnColumnSizes)
{
    *returnSize = getSize(numsSize);
    if (!nums || numsSize <= 0 || *returnSize == 0) return NULL;

    int** result = (int**)malloc(sizeof(int*) * (*returnSize));
    if (!result) return NULL;

    int* path = (int*)malloc(sizeof(int) * numsSize);
    if (!path)
    {
        free(result);
        return NULL;
    }

    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    if (!(*returnColumnSizes))
    {
        free(result);
        free(path);
        return NULL;
    }

    result[0] = (int*)malloc(sizeof(int) * 0);
    (*returnColumnSizes)[0] = 0;
    int* index = (int*)malloc(sizeof(int));
    *index = 1;

    for (int i = 0; i < numsSize; i++)
    {
        back(nums, numsSize, i, path, 0, result, index, returnColumnSizes);
    }

    free(path);
    free(index);

    return result;
}

int getSize(int num)
{
    if (num <= 0) return 0;
    return 1 << num;
}

void back(int* nums, int numsSize, int indexNums,
          int* path, int indexPath,
          int** result, int* index, int** resultColumnSizes)
{
    if (indexNums >= numsSize) return ;
    path[indexPath++] = nums[indexNums];
    
    result[*index] = (int*)malloc(sizeof(int) * indexPath);
    (*resultColumnSizes)[*index] = indexPath;
    for (int i = 0; i < indexPath; i++)
        result[*index][i] = path[i];
    (*index)++;

    for (int i = indexNums + 1; i < numsSize; i++)
    {
        back(nums, numsSize, i,
            path, indexPath,
            result, index, resultColumnSizes);
    }
}
// @lc code=end

