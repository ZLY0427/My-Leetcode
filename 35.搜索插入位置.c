/*
 * @lc app=leetcode.cn id=35 lang=c
 *
 * [35] ËÑË÷²åÈëÎ»ÖÃ
 */

// @lc code=start
int searchInsert(int* nums, int numsSize, int target)
{
    int left = 0;
    int right = numsSize - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        if (nums[middle] == target)
        {
            return middle;
        }
        else if (nums[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return left;
}
// @lc code=end

