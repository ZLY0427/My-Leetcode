/*
 * @lc app=leetcode.cn id=167 lang=c
 *
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    *returnSize = 0;
    if (!numbers || numbersSize <= 1) return NULL;

    int* result = (int*)malloc(sizeof(int) * 2);
    if (!result) return NULL;
    *returnSize = 2;

    int left = 0, right = numbersSize - 1;
    while (left < right)
    {
        int sum = numbers[left] + numbers[right];
        if (sum == target)
        {
            result[0] = left + 1;
            result[1] = right + 1;
            return result;
        }
        else if (sum < target)
            ++left;
        else
            --right;
    }

    free(result);
    *returnSize = 0;
    return NULL;
}
// @lc code=end

