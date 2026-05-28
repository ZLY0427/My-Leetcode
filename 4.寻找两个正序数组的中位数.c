/*
 * @lc app=leetcode.cn id=4 lang=c
 *
 * [4] 寻找两个正序数组的中位数
 */

// @lc code=start
#include <stdlib.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
    int numsSize = nums1Size + nums2Size;
    int* nums = (int*)malloc(sizeof(int) * numsSize);
    int i = 0, j = 0, k = 0;

    while ((i < nums1Size) && (j < nums2Size) && (k < numsSize))
    {
        if (nums1[i] == nums2[j])
        {
            nums[k] = nums1[i];
            i++;
            k++;
            nums[k] = nums2[j];
            j++;
            k++;
        }
        else if (nums1[i] < nums2[j])
        {
            nums[k] = nums1[i];
            i++;
            k++;
        }
        else
        {
            nums[k] = nums2[j];
            j++;
            k++;
        }
    }
    while ((i < nums1Size) && (k < numsSize))
    {
        nums[k] = nums1[i];
        i++;
        k++;
    }
    while ((j < nums2Size) && (k < numsSize))
    {
        nums[k] = nums2[j];
        j++;
        k++;
    }

    double result;
    if (numsSize % 2 == 0)
    {
        result = (nums[numsSize / 2] + nums[numsSize / 2 - 1]) / 2.0;
    }
    else
    {
        result = nums[numsSize / 2] * 1.0;
    }
    return result;
}
// @lc code=end

