/*
 * @lc app=leetcode.cn id=32 lang=c
 *
 * [32] 最长有效括号
 */

// @lc code=start
#include <string.h>
#include <stdbool.h>

int longestValidParentheses(char* s)
{
    int sSize = strlen(s);
    if (sSize == 0) return 0;

    int maxlen = 0;


    int left_increase = 0, right_increase = 0,left_decrease = 0, right_decrease = 0;
    for (int i = 0, j = sSize - 1; i < sSize && j >= 0; i++, j--)
    {
        // 从前向后进行遍历(无法处理"(()"这种情况, 能够处理"())"这种情况)
        if (s[i] == '(')
            left_increase++;
        else
            right_increase++;

        if (left_increase == right_increase)
            maxlen = (maxlen > 2 * right_increase) ? maxlen : 2 * right_increase;
        else if (right_increase > left_increase)
            left_increase = right_increase = 0;

        // 从后向前进行遍历(无法处理"())"这种情况, 能够处理"(()"这种情况)

        if (s[j] == ')')
            right_decrease++;
        else
            left_decrease++;
        
        if (right_decrease == left_decrease)
            maxlen = (maxlen > 2 * left_decrease) ? maxlen : 2 * left_decrease;
        else if (left_decrease > right_decrease)
            right_decrease = left_decrease = 0;

        //两种方案能够互补, 因此能够获得正确结果
    }

    return maxlen;
}
// @lc code=end

