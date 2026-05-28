/*
 * @lc app=leetcode.cn id=40 lang=c
 *
 * [40] 组合总和 II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

void sort(int* arr, int arrSize);
void Merge_Sort(int left, int right, int* arr, int* temp);
void backtrack(int* candidates, int candidatesSize, int target, 
               int* path, int pathSize, int currentSum, int start, 
               int*** result, int* returnSize, int** col_sizes);

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (candidatesSize == 0)
    {
        *returnColumnSizes = NULL;
        return NULL;
    }

    sort(candidates, candidatesSize);

    int** result = NULL;
    *returnColumnSizes = NULL;

    int* path = (int*)malloc(sizeof(int) * target);

    backtrack(candidates, candidatesSize, target, path, 0, 0, 0, 
              &result, returnSize, returnColumnSizes);

    free(path);
    return result;
}

void sort(int* arr, int arrSize)
{
    int temp[arrSize];
    Merge_Sort(0, arrSize - 1, arr, temp);
}

void Merge_Sort(int left, int right, int* arr, int* temp)
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
        if (i > start && candidates[i] == candidates[i - 1])
        {
            continue;
        }

        int num = candidates[i];
        if (currentSum + num > target) break;

        path[pathSize] = num;
        backtrack(candidates, candidatesSize, target, path, pathSize + 1,
                  currentSum + num, i + 1, result, returnSize, col_sizes);
    }
}
// @lc code=end

