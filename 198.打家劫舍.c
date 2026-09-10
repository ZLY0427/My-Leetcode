/*
 * @lc app=leetcode.cn id=198 lang=c
 *
 * [198] 打家劫舍
 */

// @lc code=start
#include <stdlib.h>

int rob(int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return -1;
    else if (numsSize == 1) return nums[0];
    else if (numsSize == 2) return nums[0] > nums[1] ? nums[0] : nums[1];

    int* dp = (int*)calloc(numsSize, sizeof(int));
    dp[0] = nums[0];

    for (int i = 1; i < numsSize; ++i)
    {
        if (i == 1)
        {
            dp[i] = nums[i] > nums[0] ? nums[i] : nums[0];
        }
        else
        {
            dp[i] = nums[i] + dp[i - 2] > dp[i - 1] ? nums[i] + dp[i - 2] : dp[i - 1];
        }
    }

    int result = dp[numsSize - 1];
    free(dp);

    return result;
}
// @lc code=end

