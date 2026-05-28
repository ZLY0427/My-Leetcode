/*
 * @lc app=leetcode.cn id=9 lang=c
 *
 * [9] »ØÎÄÊı
 */

// @lc code=start
#include <stdbool.h>

int count_digits_log10(int num);

bool isPalindrome(int x)
{
    if (x < 0)
    {
        return false;
    }
    
    int len = count_digits_log10(x);

    for (int left = 0, right = len - 1; left < right; left++, right--)
    {
        if (x / (int)pow(10, left) % 10 != x / (int)pow(10, right) % 10)
        {
            return false;
        }
    }
    return true;
}

int count_digits_log10(int num)
{
    if (num == 0)
    {
        return 1;
    }
    else
    {
        return ((int)log10(abs(num)) + 1);
    }
}
// @lc code=end

