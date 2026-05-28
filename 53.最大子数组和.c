/*
 * @lc app=leetcode.cn id=53 lang=c
 *
 * [53] 最大子数组和
 */

// @lc code=start
#include <limits.h>

int maxSubArray(int* nums, int numsSize)
{
    int maxSum = INT_MIN;
    int currentSum = 0;
    for (int i= 0; i < numsSize; i++)
    {
        currentSum += nums[i];
        if (currentSum > maxSum) maxSum = currentSum;

        if (currentSum < 0) currentSum = 0;
    }

    return maxSum;
}
// @lc code=end

