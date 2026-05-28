/*
 * @lc app=leetcode.cn id=34 lang=c
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* searchRange(int* nums, int numsSize, int target, int* returnSize)
{
    int* result = (int*)malloc(sizeof(int) * 2);
    if (!result)
    {
        *returnSize = 0;
        return NULL;
    }

    *returnSize = 2;
    result[0] = result[1] = -1;
    if (!numsSize || target < nums[0] || nums[numsSize - 1] < target)
    {
        return result;
    }

    if (numsSize == 1 && nums[0] == target)
    {
        result[0] = result[1] = 0;
    }

    int left = 0, right = numsSize - 1;
    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        if (nums[middle] == target)
        {
            int leftindex = middle - 1, rightindex = middle + 1;
            while (leftindex >= 0 && nums[leftindex] == target)
            {
                leftindex--;
            }
            while (rightindex <= numsSize - 1 && nums[rightindex] == target)
            {
                rightindex++;
            }
            result[0] = leftindex + 1;
            result[1] = rightindex - 1;
            break;
        }
        else if (nums[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return result;
}
// @lc code=end

