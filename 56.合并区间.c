/*
 * @lc app=leetcode.cn id=56 lang=c
 *
 * [56] 合并区间
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

void mergeSortHelper(int** arr, int left, int mid, int right);
void mergeSort(int** arr, int left, int right);

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes)
{
    // 初始化
    (*returnSize) = 0;

    // 特殊情况
    if (!intervals) return NULL;

    if (intervalsSize <= 0 || intervalsColSize[0] != 2) return NULL;

    // 声明结果
    int** result = (int**)malloc(sizeof(int*) * intervalsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * intervalsSize);
    if (!result || !(*returnColumnSizes)) return NULL;

    for (int i = 0; i < intervalsSize; i++)
    {
        result[i] = (int*)malloc(sizeof(int) * 2);

        (*returnColumnSizes)[i] = 2;
    }

    // 防止更改传入数据
    int** copy = (int**)malloc(sizeof(int*) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++)
    {
        copy[i] = (int*)malloc(sizeof(int) * 2);
        copy[i][0] = intervals[i][0];
        copy[i][1] = intervals[i][1];
    }

    // 排序
    mergeSort(copy, 0, intervalsSize - 1);

    // 合并
    result[0][0] = copy[0][0], result[0][1] = copy[0][1];
    *returnSize = 1;
    for (int i = 1; i < intervalsSize; i++)
    {
        if (copy[i][0] <= result[*returnSize - 1][1])
        {
            int newEnd = (result[*returnSize - 1][1] > copy[i][1]) ? result[*returnSize - 1][1] : copy[i][1];
            result[*returnSize - 1][1] = newEnd;
        }
        else
        {
            result[(*returnSize)][0] = copy[i][0];
            result[(*returnSize)][1] = copy[i][1];
            (*returnSize)++;
        }
    }

    // 释放临时数组
    for (int i = 0; i < intervalsSize; i++)
    {
        free(copy[i]);
    }
    free(copy);

    // 缩小空间
    for (int i = *returnSize; i < intervalsSize; i++)
    {
        free(result[i]);
    }

    int* temp1 = (int*)realloc(*returnColumnSizes, sizeof(int) * (*returnSize));
    *returnColumnSizes = temp1;

    int** temp2 = (int**)realloc(result, sizeof(int*) * (*returnSize));
    result = temp2;

    return result;
}

void mergeSortHelper(int** arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组
    int** L = (int**)malloc(sizeof(int*) * n1);
    int** R = (int**)malloc(sizeof(int*) * n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i][0] <= R[j][0]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}


void mergeSort(int** arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        mergeSortHelper(arr, left, mid, right);
    }
}
// @lc code=end

