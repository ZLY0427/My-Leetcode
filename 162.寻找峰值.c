/*
 * @lc app=leetcode.cn id=162 lang=c
 *
 * [162] 寻找峰�?
 */

// @lc code=start
int findPeakElement(int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return -1;
    if (numsSize == 1) return 0;

    for (int i = 0; i < numsSize; ++i)
    {
        if (i == 0)
        {
            if (nums[i] > nums[i + 1]) return i;
        }
        else if (i == numsSize - 1)
        {
            if (nums[i] > nums[i - 1]) return i;
        }
        else
        {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) return i;
        }
    }

    return -1;
}
// @lc code=end

