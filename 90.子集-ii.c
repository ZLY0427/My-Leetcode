/*
 * @lc app=leetcode.cn id=90 lang=c
 *
 * [90] 子集 II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

void Merge(int len, int *arr);
void Merge_Sort(int left, int right, int *arr, int *temp);
void backtrack(int start, int pathLen, int** result,
               int* returnSize, int* path, int** returnColumnSizes,
               int* nums, int numsSize);

int** subsetsWithDup(int* nums, int numsSize,
                     int* returnSize, int** returnColumnSizes)
{
    if (!nums || numsSize <= 0)
    {
        (*returnSize) = 0;
        (*returnColumnSizes) = NULL;
        return NULL;
    }

    Merge(numsSize, nums);

    int maxSize = 1 << numsSize;
    int** result = (int**)malloc(sizeof(int*) * maxSize);
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * maxSize);
    (*returnSize) = 0;

    if (!result || !(*returnColumnSizes))
    {
        free(result);
        free(*returnColumnSizes);
        (*returnSize) = 0;
        (*returnColumnSizes) = NULL;
        return NULL;
    }

    int* path = (int*)malloc(sizeof(int) * numsSize);
    if (!path)
    {
        free(result);
        free(*returnColumnSizes);
        (*returnSize) = 0;
        (*returnColumnSizes) = NULL;
        return NULL;
    }

    
    backtrack(0, 0, result, returnSize, path,
              returnColumnSizes, nums, numsSize);

    free(path);

    return result;
}

void Merge(int len, int *arr)
{
    int* temp = (int*)malloc(sizeof(int) * len);
    if (!temp) return ;
    Merge_Sort(0, len - 1, arr, temp);
    free(temp);
}

void Merge_Sort(int left, int right, int *arr, int *temp)
{
    if (left >= right)
    {
        return;
    }
    int middle = (left + right) / 2;
    Merge_Sort(left, middle, arr, temp);
    Merge_Sort(middle + 1, right, arr, temp);
    int len_left = middle - left + 1;
    int len_right = right - middle;
    int i, j, k;
    for(i = 0, j = 0, k = left; (i < len_left) && (j < len_right); k++)
    {
        if (arr[left + i] < arr[middle + 1 + j])
        {
            temp[k] = arr[left + i];
            i++;
        }
        else
        {
            temp[k] = arr[middle + 1 + j];
            j++;
        }
    }
    if (i < len_left)
    {
        for (; i < len_left; i++, k++)
        {
            temp[k] = arr[left + i];
        }
    }
    if (j < len_right)
    {
        for (; j < len_right; j++, k++)
        {
            temp[k] = arr[middle + 1 + j];
        }
    }
    for (k = left; k <= right; k++)
    {
        arr[k] = temp[k];
    }
}

void backtrack(int start, int pathLen, int** result,
               int* returnSize, int* path, int** returnColumnSizes,
               int* nums, int numsSize)
{
    result[*returnSize] = (int*)malloc(sizeof(int) * pathLen);
    memcpy(result[*returnSize], path, sizeof(int) * pathLen);
    (*returnColumnSizes)[*returnSize] = pathLen;
    (*returnSize)++;

    for (int i = start; i < numsSize; i++)
    {
        if (i > start && nums[i] == nums[i-1]) continue;
            
        path[pathLen] = nums[i];
        backtrack(i + 1, pathLen + 1, result, returnSize,
                  path, returnColumnSizes, nums, numsSize);
    }
}
// @lc code=end
