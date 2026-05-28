/*
 * @lc app=leetcode.cn id=80 lang=c
 *
 * [80] 删除有序数组中的重复项 II
 */

// @lc code=start
int removeDuplicates(int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return 0;
    if (numsSize <= 2) return numsSize;

    int slow = 2, fast = 2;
    while (fast < numsSize && slow <= fast)
    {
        if (nums[fast] == nums[slow - 2]) fast++;
        else nums[slow++] = nums[fast++];
    }

    return slow;
}
// @lc code=end

