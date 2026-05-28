/*
 * @lc app=leetcode.cn id=46 lang=c
 *
 * [46] 全排列
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

int getFactorial(int n);
void Merge(int len, int *arr);
int* getNextArr(int* nums, int numsSize);
void Merge_Sort(int left, int right, int *arr, int *temp);
void copyForIntArr(int* resultArr, int* copyArr, int arrSize);

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    if (!nums || numsSize <= 0) return NULL;

    *returnSize = getFactorial(numsSize);

    int** result = (int**)malloc(sizeof(int*) * (*returnSize));
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));

    if (!result || !*returnColumnSizes)
    {
        free(result);
        free(*returnColumnSizes);
        *returnSize = 0;
        return NULL;
    }

    for (int indexForMalloc = 0; indexForMalloc < (*returnSize); indexForMalloc++)
    {
        (*returnColumnSizes)[indexForMalloc] = numsSize;
        result[indexForMalloc] = (int*)malloc(sizeof(int) * ((*returnColumnSizes)[indexForMalloc]));
        if (!result[indexForMalloc])
        {
            for (int indexForFree = 0; indexForFree < indexForMalloc; indexForFree++)
            {
                free(result[indexForFree]);
            }
            free(result);
            return NULL;
        }
    }

    int* tempNums = (int*)malloc(sizeof(int) * numsSize);
    if (!tempNums)
    {
        for (int indexForFree = 0; indexForFree < (*returnSize); indexForFree++)
        {
            free(result[indexForFree]);
        }
        free(result);
        return NULL;
    }

    copyForIntArr(tempNums, nums, numsSize);

    Merge(numsSize, tempNums);

    copyForIntArr(result[0], tempNums, numsSize);

    for (int index = 1; index < (*returnSize); index++)
    {
        result[index] = getNextArr(result[index - 1], numsSize);
    }

    return result;
}

int getFactorial(int n)
{
    if (n < 0) return 0;
    else if (n == 0) return 1;
    int result = 1;
    for (int i = n; i > 0; i--)
    {
        result *= i;
    }
    return result;
}

void Merge(int len, int *arr)
{
    if (len <= 0) return ;

    int* temp = (int*)malloc(sizeof(int) * len);
    if (!temp)
    {
        printf("内存分配错误!\n");
        return ;
    }
    Merge_Sort(0, len - 1, arr, temp);
    free(temp);
}

void Merge_Sort(int left, int right, int *arr, int *temp)
{
    if (left >= right)
    {
        return;
    }
    int middle = left + (right - left) / 2;
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

void copyForIntArr(int* resultArr, int* copyArr, int arrSize)
{
    if (arrSize < 1) return ;
    for (int i = 0; i < arrSize; i++)
    {
        resultArr[i] = copyArr[i];
    }
}

int* getNextArr(int* nums, int numsSize)
{
    if (numsSize < 1) return NULL;

    int* result = (int*)malloc(sizeof(int) * numsSize);
    if (!result) return NULL;

    copyForIntArr(result, nums, numsSize);
    if (numsSize < 2) return result;

    int i = numsSize - 2;
    while (i >= 0 && result[i] >= result[i + 1])
    {
        i--;
    }

    if (i >= 0)
    {
        int j = numsSize - 1;
        while (result[j] <= result[i])
        {
            j--;
        }
        int temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }

    int left = i + 1;
    int right = numsSize - 1;
    while (left < right)
    {
        int temp = result[left];
        result[left] = result[right];
        result[right] = temp;
        left++;
        right--;
    }

    return result;
}
// @lc code=end

