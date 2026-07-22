/*
 * @lc app=leetcode.cn id=137 lang=c
 *
 * [137] 只出现一次的数字 II
 */

// @lc code=start
int singleNumber(int* nums, int numsSize)
{
    int ones = 0, twos = 0;
    for (int i = 0; i < numsSize; ++i)
    {
        ones = (ones ^ nums[i]) & ~twos;
        twos = (twos ^ nums[i]) & ~ones;
    }
    return ones;
}
// @lc code=end

