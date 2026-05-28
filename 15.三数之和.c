/*
 * @lc app=leetcode.cn id=15 lang=c
 *
 * [15] 三数之和
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


int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) 
{
    *returnSize = 0;
    if(numsSize < 3)
    {
        *returnColumnSizes = NULL;
        return NULL;
    }

    int initialCapacity = numsSize;
    int** result = (int**)malloc(sizeof(int*) * initialCapacity);
    *returnColumnSizes = (int*)malloc(sizeof(int) * initialCapacity);

    Sort(nums, numsSize);

    if (nums[0] + nums[1] + nums[2] > 0 || 
        nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3] < 0)
    {
        free(result);
        free(*returnColumnSizes);
        *returnColumnSizes = NULL;
        return NULL;
    }

    for (int i = 0; i < numsSize - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i-1])
        {
            continue;
        }
        int left = i + 1;
        int right = numsSize - 1;
        
        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum == 0)
            {
                if (*returnSize >= initialCapacity)
                {
                    initialCapacity += numsSize;
                    result = (int**)realloc(result, sizeof(int*) * initialCapacity);
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, sizeof(int) * initialCapacity);
                }
                
                result[*returnSize] = (int*)malloc(sizeof(int) * 3);
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
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
            else if (sum < 0)
            {
                left++;
            }
            else
            {
                right--;
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

