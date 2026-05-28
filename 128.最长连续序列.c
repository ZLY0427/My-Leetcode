/*
 * @lc app=leetcode.cn id=128 lang=c
 *
 * [128] 最长连续序列
 */

// @lc code=start
#include <stdlib.h>
#include <stdbool.h>

void Merge(int len, int *arr);
void Merge_Sort(int left, int right, int *arr, int *temp);

int longestConsecutive(int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return 0;

    Merge(numsSize, nums);

    int max = 1;
    int count = 1;
    for (int i = 1; i < numsSize; ++i)
    {
        if (nums[i] - nums[i - 1] == 0) continue;
        else if (nums[i] - nums[i - 1] == 1) ++count;
        else count = 1;

        max = max > count ? max : count;
    }

    return max;
}

// 中间数组
void Merge(int len, int *arr)
{
    int* temp = (int*)malloc(sizeof(int) * len);
    Merge_Sort(0, len - 1, arr, temp);
    free(temp);
}

// 归并排序主体
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
// @lc code=end

