/*
 * @lc app=leetcode.cn id=152 lang=c
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
#include <stdlib.h>

int getMax(int num1, int num2, int num3);
int getMin(int num1, int num2, int num3);

int maxProduct(int* nums, int numsSize)
{
    if (!nums || numsSize <= 0) return 0;
    
    int max = nums[0];
    int min = nums[0];
    int result = max;

    for (int i = 1; i < numsSize; ++i)
    {
        int temp_max = max;
        int temp_min = min;
        max = getMax(nums[i], temp_max * nums[i], temp_min * nums[i]);
        min = getMin(nums[i], temp_max * nums[i], temp_min * nums[i]);
        result = result > max ? result : max;
    }
    return result;
}

int getMax(int num1, int num2, int num3)
{
    return num1 > num2 ? (num1 > num3 ? num1 : num3) : (num2 > num3 ? num2 : num3);
}

int getMin(int num1, int num2, int num3)
{
    return num1 < num2 ? (num1 < num3 ? num1 : num3) : (num2 < num3 ? num2 : num3);
}
// @lc code=end

