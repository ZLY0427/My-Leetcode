/*
 * @lc app=leetcode.cn id=81 lang=c
 *
 * [81] ËÑË÷Ğı×ªÅÅĞòÊı×é II
 */

// @lc code=start
#include <stdbool.h>

bool search(int* nums, int numsSize, int target)
{
    if (!nums || numsSize <= 0) return false;
    int left = 0, right = numsSize - 1;
    
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (target == nums[left] || target == nums[right] || target == nums[middle]) return true;
        if (nums[left] > nums[middle])
        {
            if (nums[middle] < target && target < nums[right]) left = middle + 1;
            else right = middle;
        }
        else if (nums[left] == nums[middle])
        {
            left++;
        }
        else
        {
            if (nums[left] < target && target < nums[middle]) right = middle;
            else left = middle + 1;
        }
    }

    return false;
}
// @lc code=end

