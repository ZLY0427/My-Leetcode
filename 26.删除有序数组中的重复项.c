/*
 * @lc app=leetcode.cn id=26 lang=c
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
int removeDuplicates(int* nums, int numsSize)
{
    if (numsSize < 0)
    {
        return 0;
    }
    int slow = 1;
    for (int fast = 1; fast < numsSize; fast++)
    {
        if (nums[fast] != nums[slow - 1])
        {
            nums[slow++] = nums[fast];
        }
    }
    return slow;
}
// @lc code=end

