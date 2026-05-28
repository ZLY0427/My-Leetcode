/*
 * @lc app=leetcode.cn id=7 lang=c
 *
 * [7] 整数反转
 */

// @lc code=start
#include <math.h>
#include <limits.h>
#include <stdbool.h>

int reverse(int x)
{
    int result = 0;
    while (x != 0)
    {
        int temp = (int)(x % 10);
        if ((result > INT_MAX / 10 || (result == INT_MAX / 10 && temp > 7)) || 
           (result < INT_MIN / 10 || (result == INT_MIN / 10 && temp < -8)))
        {
            return 0;
        }
        result = result * 10 + temp;
        x = x / 10;
    }
    return result;
}
// @lc code=end
