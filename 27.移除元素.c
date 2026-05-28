/*
 * @lc app=leetcode.cn id=27 lang=c
 *
 * [27] ÒÆ³ıÔªËØ
 */

// @lc code=start
int removeElement(int* nums, int numsSize, int val)
{
    if (numsSize < 0)
    {
        return 0;
    }

    int slow = 0;
    for (int fast = 0; fast < numsSize; fast++)
    {
        if (nums[fast] != val)
        {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}
// @lc code=end

