/*
 * @lc app=leetcode.cn id=33 lang=c
 *
 * [33] 搜索旋转排序数组
 */

// @lc code=start
// @lc app=leetcode.cn id=33 lang=c
// @lc code=start

// 标准二分查找：在闭区间[left, right]中找target，返回索引或-1
int getLocated(int* nums, int left, int right, int target);
int getIndex(int* nums, int numsSize);

int search(int* nums, int numsSize, int target)
{
    if (numsSize == 0)
        return -1;
    if (numsSize == 1)
    {
        return nums[0] == target ? 0 : -1;
    }
    
    int index = getIndex(nums, numsSize);

    if (index > 0 && nums[0] <= target && target <= nums[index - 1])
    {
        return getLocated(nums, 0, index - 1, target);
    }
    else
    {
        return getLocated(nums, index, numsSize - 1, target);
    }
}

int getIndex(int* nums, int numsSize)
{
    int left = 0, right = numsSize - 1;
    if (nums[left] < nums[right])
    { 
        return 0;
    }

    while (left < right)
    {
        int middle = left + (right - left) / 2;
        if (nums[middle] > nums[right])
        {
            left = middle + 1;
        }
        else
        {
            right = middle;
        }
    }

    return left;
}

int getLocated(int* nums, int left, int right, int target)
{
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

    return -1;
}
// @lc code=end

