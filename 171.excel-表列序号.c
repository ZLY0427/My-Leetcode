/*
 * @lc app=leetcode.cn id=171 lang=c
 *
 * [171] Excel 表列序号
 */

// @lc code=start
#include <string.h>

int titleToNumber(char* columnTitle)
{
    
    int len = strlen(columnTitle);
    if (!columnTitle || len < 0) return -1;

    long long result = 0;
    for (int i = 0; i < len; ++i)
        result = result * 26 + columnTitle[i] - 'A' + 1;

    return (int)result;
}
// @lc code=end

