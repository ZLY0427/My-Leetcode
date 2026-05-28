/*
 * @lc app=leetcode.cn id=29 lang=c
 *
 * [29] БЅКэПаіэ
 */

// @lc code=start
#include <limits.h>
#include <stdbool.h>

int divide(int dividend, int divisor)
{
    if (divisor == 1) return dividend;
    if (divisor == -1) return dividend == INT_MIN ? INT_MAX : -dividend;
    
    bool is_negative = (dividend > 0) != (divisor > 0);
    
    if (dividend > 0) dividend = -dividend;
    if (divisor > 0) divisor = -divisor;
    
    int quotient = 0;
    while (dividend <= divisor)
    {
        int current_divisor = divisor;
        int current_count = 1;
        
        while (current_divisor >= dividend - current_divisor)
        {
            current_divisor += current_divisor;
            current_count += current_count;
        }
        
        dividend -= current_divisor;
        quotient += current_count;
    }
    
    return is_negative ? -quotient : quotient;
}
// @lc code=end

