/*
 * @lc app=leetcode.cn id=47 lang=c
 *
 * [47] 全排列 II
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int getMaxSize(int n);
void sortArray(int* nums, int numsSize);
void mergeSort(int* nums, int left, int right, int* temp);
void merge(int* nums, int left, int mid, int right, int* temp);
void backtrack(int* nums, int numsSize, int* path,
               int pathLen, int* used, int** result,
               int* returnSize, int* returnColumnSizes);
/*
    nums 原数组
    numsSize 原数组大小
    path 当前选择的路径
    pathLen 当前选择的长度
    used 记录对应索引的数字是否被使用
    result 结果
    resultSize 结果大小
    returnColumnSizes 每个结果大小(应该均为numsSize)
    nowSize 当前result的大小(方便大小不足时扩展)
*/


int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    (*returnSize) = 0;
    if (!nums || numsSize < 1) return NULL;

    sortArray(nums, numsSize);

    int maxSize = getMaxSize(numsSize);
    int** result = (int**)malloc(sizeof(int*) * maxSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * maxSize);
    if (!result || !(*returnColumnSizes))
    {
        free(result);
        free(*returnColumnSizes);
        return NULL;
    }

    int* path = (int*)malloc(sizeof(int) * numsSize);
    int* used = (int*)calloc(numsSize, sizeof(int));

    backtrack(nums, numsSize, path, 0, used,
              result, returnSize, *returnColumnSizes);

    free(path);
    free(used);

    result = (int**)realloc(result, sizeof(int*) * (*returnSize));
    *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * (*returnSize));

    return result;
}

void backtrack(int* nums, int numsSize, int* path,
               int pathLen, int* used, int** result,
               int* returnSize, int* returnColumnSizes)
{
    if (pathLen == numsSize)
    {
        result[*returnSize] = (int*)malloc(sizeof(int) * numsSize);
        memcpy(result[*returnSize], path, sizeof(int) * numsSize);
        returnColumnSizes[*returnSize] = numsSize;
        (*returnSize)++;
        return ;
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) continue;

        used[i] = 1;
        path[pathLen] = nums[i];
        backtrack(nums, numsSize, path, pathLen + 1, used, result, returnSize, returnColumnSizes);
        used[i] = 0;
    }
}

int getMaxSize(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++)
    {
        result = result * i;
    }
    return result;
}

void merge(int* nums, int left, int mid, int right, int* temp)
{
    int i = left, j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (nums[i] <= nums[j])
        {
            temp[k++] = nums[i++];
        }
        else
        {
            temp[k++] = nums[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = nums[i++];
    }
    while (j <= right)
    {
        temp[k++] = nums[j++];
    }

    for (int idx = left; idx <= right; idx++)
    {
        nums[idx] = temp[idx];
    }
}

void mergeSort(int* nums, int left, int right, int* temp)
{
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid, temp);
    mergeSort(nums, mid + 1, right, temp);
    merge(nums, left, mid, right, temp);
}

void sortArray(int* nums, int numsSize)
{
    if (nums == NULL || numsSize <= 1) return;

    int* temp = (int*)malloc(sizeof(int) * numsSize);
    if (temp == NULL) return;

    mergeSort(nums, 0, numsSize - 1, temp);

    free(temp);
}
// @lc code=end

