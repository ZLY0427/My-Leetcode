/*
 * @lc app=leetcode.cn id=10 lang=c
 *
 * [10] 正则表达式匹配
 */

// @lc code=start
#include <stdbool.h>

bool isMatch(char* s, char* p)
{
    if (*p == '\0')
    {
        return *s == '\0';
    }

    bool firstMatch = (*s != '\0') && (*s == *p || *p == '.');

    if (*(p + 1) == '*')
    {
        return (isMatch(s, p + 2) || (firstMatch && isMatch(s + 1, p)));
    }
    else
    {
        return (firstMatch && isMatch(s + 1, p + 1));
    }
}
// @lc code=end

