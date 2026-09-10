/*
 * @lc app=leetcode.cn id=189 lang=c
 *
 * [189] 轮转数组
 */

// @lc code=start
#include <stdlib.h>

void rotate(int* nums, int numsSize, int k)
{
    if (!nums || numsSize <= 1 || k <= 0) return ;
    int move_count = k % numsSize;

    int* temp = (int*)malloc(sizeof(int) * move_count);
    if (!temp) return ;

    for (int i = 0; i < move_count; ++i)
        temp[i] = nums[numsSize - move_count + i];

    for (int i = numsSize - 1; i >= move_count; --i)
        nums[i] = nums[i - move_count];

    for (int i = 0; i < move_count; ++i)
        nums[i] = temp[i];

    free(temp);
}
// @lc code=end

