/*
 * @lc app=leetcode.cn id=42 lang=c
 *
 * [42] Ω””ÍÀÆ
 */

// @lc code=start
#include <stdlib.h>

int trap(int* height, int heightSize)
{
    if (height == NULL && heightSize < 0) return 0;
    
    int volume = 0;
    int left = 0;
    int right = heightSize - 1;
    int left_max_height = 0;
    int right_max_height = 0;
    
    while (left < right)
    {
        if (height[left] < height[right])
        {
            if (height[left] >= left_max_height)
            {
                left_max_height = height[left];
            }
            else
            {
                volume += left_max_height - height[left];
            }
            left++;
        }
        else
        {
            if (height[right] >= right_max_height)
            {
                right_max_height = height[right];
            }
            else
            {
                volume += right_max_height - height[right];
            }
            right--;
        }
    }

    return volume;
}
// @lc code=end

