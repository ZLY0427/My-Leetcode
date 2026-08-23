/*
 * @lc app=leetcode.cn id=169 lang=c
 *
 * [169] 多数元素
 */

// @lc code=start
#include <stdlib.h> 

typedef struct {
    int val;
    int count;
} Number;

int majorityElement(int* nums, int numsSize)
{
    Number* n = (Number*)malloc(sizeof(Number));
    n -> val = nums[0];
    n -> count = 1;

    for (int i = 1; i < numsSize; ++i)
    {
        if (nums[i] == n -> val) ++n -> count;
        else if (n -> count == 0)
        {
            n -> val = nums[i];
            n -> count = 1;
        }
        else --n -> count;
    }

    int result = n -> val;
    
    free(n);

    return result;
}
// @lc code=end

