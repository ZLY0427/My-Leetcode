/*
 * @lc app=leetcode.cn id=91 lang=c
 *
 * [91] 解码方法
 */

// @lc code=start
#include <stdlib.h>
#include <string.h>

int numDecodings(char* s)
{
    if (!s || strlen(s) <= 0) return 0;
    if (s[0] == '0') return 0;

    int sSize = strlen(s);
    int* dp = (int*)malloc(sizeof(int) * (sSize + 1));
    if (!dp) return 0;

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= sSize; i++)
    {
        dp[i] = 0;

        // 情况1：单独解码第i个字符（对应原字符串s[i-1]）
        if (s[i-1] != '0') dp[i] += dp[i-1];

        // 情况2：第i-1和i个字符组合解码（对应原字符串s[i-2]和s[i-1]）
        int twoDigit = (s[i-2] - '0') * 10 + (s[i-1] - '0');
        if (twoDigit >= 10 && twoDigit <= 26) dp[i] += dp[i-2];
    }

    int result = dp[sSize];
    free(dp);
    return result;
}
// @lc code=end

