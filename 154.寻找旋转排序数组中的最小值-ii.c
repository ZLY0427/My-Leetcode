/*
 * @lc app=leetcode.cn id=154 lang=c
 *
 * [154] 寻找旋转排序数组中的最小�? II
 */

// @lc code=start
int findMin(int* nums, int numsSize)
{
    int min = nums[0];
    for (int i = 1; i < numsSize; ++i)
        min = min < nums[i] ? min : nums[i];

    return min;
}
// @lc code=end

