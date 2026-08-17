/*
 * @lc app=leetcode.cn id=153 lang=c
 *
 * [153] 寻找旋转排序数组中的最小�?
 */

// @lc code=start
int binarySearch(int* nums, int left, int right)
{
    if (left == right) return nums[left];
    int middle = (left + right) / 2;
    if (nums[middle] > nums[right])
    {
        return binarySearch(nums, middle + 1, right);
    }
    else
    {
        return binarySearch(nums, left, middle);
    }
}

int findMin(int* nums, int numsSize)
{
    return binarySearch(nums, 0, numsSize - 1);
}
// @lc code=end

