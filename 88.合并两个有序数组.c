/*
 * @lc app=leetcode.cn id=88 lang=c
 *
 * [88] 合并两个有序数组
 */

// @lc code=start
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
    int result[m + n];
    int i = 0, j = 0, k = 0;
    while (i < nums1Size && i < m && j < nums2Size && j < n)
    {
        if (nums1[i] == nums2[j])
        {
            result[k] = nums1[i];
            i++;
            k++;
            result[k] = nums2[j];
            j++;
            k++;
        }
        else if(nums1[i] < nums2[j])
        {
            result[k] = nums1[i];
            i++;
            k++;
        }
        else
        {
            result[k] = nums2[j];
            j++;
            k++;
        }
    }
    while (i < nums1Size && i < m)
    {
        result[k] = nums1[i];
        i++;
        k++;
    }
    while (j < nums2Size && j < n)
    {
        result[k] = nums2[j];
        j++;
        k++;
    }

    for (int p = 0; p < nums1Size; p++)
    {
        nums1[p] = result[p];
    }
}
// @lc code=end

