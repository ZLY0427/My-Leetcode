/*
 * @lc app=leetcode.cn id=18 lang=c
 *
 * [18] 四数之和
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

void Sort(int* arr, int size);
void Merge_Sort(int* arr, int left, int right, int* temp);

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (numsSize < 4)
    {
        return NULL;
    }

    int initialCapacity = numsSize;
    int** result = (int**)malloc(sizeof(int*) * initialCapacity);
    *returnColumnSizes = (int*)malloc(sizeof(int) * initialCapacity);

    Sort(nums, numsSize);

    if ((long long)nums[0] + nums[1] + nums[2] + nums[3]> target || 
        (long long)nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3] + nums[numsSize - 4] < target)
    {
        free(result);
        free(*returnColumnSizes);
        *returnColumnSizes = NULL;
        return NULL;
    }

    for (int i = 0; i < numsSize; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        for (int j = i + 1; j < numsSize; j++)
        {
            if (j > i + 1 && nums[j] == nums[j - 1])
            {
                continue;
            }
            int left = j + 1;
            int right = numsSize - 1;

            while (left < right)
            {
                long long sum = (long long)nums[i] + nums[left] + nums[right] + nums[j];

                if (sum == target)
                {
                    if (*returnSize >= initialCapacity)
                    {
                        initialCapacity += numsSize;
                        result = (int**)realloc(result, sizeof(int*) * initialCapacity);
                        *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * initialCapacity);
                    }

                    result[*returnSize] = (int*)malloc(sizeof(int) * 4);
                    result[*returnSize][0] = nums[i];
                    result[*returnSize][1] = nums[j];
                    result[*returnSize][2] = nums[left];
                    result[*returnSize][3] = nums[right];
                    (*returnColumnSizes)[*returnSize] = 4;
                    (*returnSize)++;

                    while (left < right && nums[left] == nums[left + 1])
                    {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1])
                    {
                        right--;
                    }    

                    left++;
                    right--;
                }
                else if (sum > target)
                {
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }
    }

    result = (int**)realloc(result, sizeof(int*) * (*returnSize));
    *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * (*returnSize));

    return result;
}

void Sort(int* arr, int size)
{
    int* temp = (int*)malloc(sizeof(int) * size);
    Merge_Sort(arr, 0, size - 1, temp);
    free(temp);
}

void Merge_Sort(int* arr, int left, int right, int* temp)
{
    if (left >= right)
    {
        return ;
    }
    int middle = (left + right) / 2;
    Merge_Sort (arr, left, middle, temp);
    Merge_Sort (arr, middle + 1, right, temp);

    int len_left = middle - left + 1;
    int len_right = right - middle;

    for (int i = 0; i < len_left; i++)
    {
        temp[left + i] = arr[left + i];
    }
    for (int j = 0; j < len_right; j++)
    {
        temp[middle + 1 + j] = arr[middle + 1 + j];
    }

    int i, j, k;

    for(i = 0, j = 0, k = left; (i < len_left) && (j < len_right); k++)
    {
        if (temp[left + i] < temp[middle + 1 + j])
        {
            arr[k] = temp[left + i];
            i++;
        }
        else
        {
            arr[k] = temp[middle + 1 + j];
            j++;
        }
    }

    while (i < len_left)
    {
        arr[k] = temp[left + i];
        i++;
        k++;
    }

    while (j < len_right)
    {
        arr[k] = temp[middle + 1 + j];
        j++;
        k++;
    }
}

// @lc code=end

