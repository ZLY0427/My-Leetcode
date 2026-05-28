/*
 * @lc app=leetcode.cn id=57 lang=c
 *
 * [57] 插入区间
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <stdbool.h>

bool isIntersect(int* arr1, int* arr2);

int** insert(int** intervals, int intervalsSize, int* intervalsColSize,
             int* newInterval, int newIntervalSize, int* returnSize,
             int** returnColumnSizes)
{
    (*returnSize) = 0;

    int maxSize = intervalsSize + 1;
    int** result = (int**)malloc(sizeof(int*) * maxSize);
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * maxSize);
    if (!result || !(*returnColumnSizes))
    {
        free(result);
        free(*returnColumnSizes);
        (*returnSize) = 0;
        return NULL;
    }
    int i = 0;

    // 1. 添加所有在 newInterval 左侧且不重叠的区间
    while (i < intervalsSize && intervals[i][1] < newInterval[0])
    {
        result[*returnSize] = (int*)malloc(sizeof(int) * 2);
        result[*returnSize][0] = intervals[i][0];
        result[*returnSize][1] = intervals[i][1];
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;
        i++;
    }

    // 2. 合并所有与 newInterval 重叠的区间
    while (i < intervalsSize && isIntersect(intervals[i], newInterval))
    {
        newInterval[0] = (intervals[i][0] < newInterval[0]) ? intervals[i][0] : newInterval[0];
        newInterval[1] = (intervals[i][1] > newInterval[1]) ? intervals[i][1] : newInterval[1];
        i++;
    }

    // 插入合并后的新区间
    result[*returnSize] = (int*)malloc(sizeof(int) * 2);
    result[*returnSize][0] = newInterval[0];
    result[*returnSize][1] = newInterval[1];
    (*returnColumnSizes)[*returnSize] = 2;
    (*returnSize)++;

    // 3. 添加右侧不重叠的区间
    while (i < intervalsSize)
    {
        result[*returnSize] = (int*)malloc(sizeof(int) * 2);
        result[*returnSize][0] = intervals[i][0];
        result[*returnSize][1] = intervals[i][1];
        (*returnColumnSizes)[*returnSize] = 2;
        (*returnSize)++;
        i++;
    }

    // realloc 缩小内存
    int** temp1 = (int**)realloc(result, sizeof(int*) * (*returnSize));
    if (temp1) result = temp1;

    int* temp2 = (int*)realloc((*returnColumnSizes), sizeof(int) * (*returnSize));
    if (temp2) (*returnColumnSizes) = temp2;

    return result;
}

bool isIntersect(int* arr1, int* arr2)
{
    return arr1[1] >= arr2[0] && arr2[1] >= arr1[0];
}
// @lc code=end

