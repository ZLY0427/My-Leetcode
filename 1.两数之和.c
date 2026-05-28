/*
 * @lc app=leetcode.cn id=1 lang=c
 *
 * [1] 两数之和
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    //处理特殊情况
    if (!nums || numsSize < 2)
        return NULL;

    // 初始化存储结果及返回值的大小
    int* result = (int*)malloc(sizeof(int) * 2);
    if (!result) 
        return NULL;
    *returnSize = 0;

    // 双循环计算结果
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
        }
    }

    // 特殊情况处理
    free(result);
    return NULL;
}

// @lc code=end
