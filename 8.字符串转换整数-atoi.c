/*
 * @lc app=leetcode.cn id=8 lang=c
 *
 * [8] 8.×Ö·û´®×ª»»ÕûÊý (atoi)
 */

// @lc code=start
#include <stdbool.h>
#include <limits.h>

int myAtoi(char* s)
{
    int len = strlen(s);
    bool is_first = true;

    int result = 0;
    int sign = 1;
    int i = 0;

    while (i < len && s[i] == ' ')
    {
        i++;
    }

    if (i < len && (s[i] == '+' || s[i] == '-'))
    {
        if (s[i] == '+')
        {
            sign = 1;
        }
        else
        {
            sign = -1;
        }
        i++;
    }

    while (i < len && s[i] >= '0' && s[i] <= '9')
    {
        int val = s[i] - '0';

        if (sign == 1)
        {
            if (result > INT_MAX / 10 || (result == INT_MAX / 10 && val > 7))
            {
                return INT_MAX;
            }
        }
        else
        {
            if (result < INT_MIN / 10 || (result == INT_MIN / 10 && val > 8))
            {
                return INT_MIN;
            }
        }
        result = result * 10 + val * sign;
        i++;
    }

    return result;
}
// @lc code=end

