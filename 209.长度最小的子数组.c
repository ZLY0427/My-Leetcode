/*
 * @lc app=leetcode.cn id=209 lang=c
 *
 * [209] 长度最小的子数�?
 */

// @lc code=start
#include <stdlib.h>

int minSubArrayLen(int target, int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return 0;
    
    int result = numsSize + 1;
    int left = 0, right = 0;
    int sum = 0;

    while (left <= right && right < numsSize)
    {
        sum += nums[right];
        while (left <= right && sum >= target)
        {
            int lenth = right - left + 1;
            result = result < lenth ? result : lenth;
            sum -= nums[left++];
        }
        ++right;
    }

    return result > numsSize ? 0 : result;
}
// @lc code=end

