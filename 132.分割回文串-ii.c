/*
 * @lc app=leetcode.cn id=132 lang=c
 *
 * [132] 分割回文串 II
 */

// @lc code=start
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int minCut(char* s)
{
    int n = strlen(s);
    // isPal[i][j]：s[i...j] 是否回文
    bool** isPal = (bool**)malloc(sizeof(bool*) * n);
    for (int i = 0; i < n; ++i)
    {
        isPal[i] = (bool*)calloc(n, sizeof(bool));
        isPal[i][i] = true;
    }

    // 预处理所有长度>=2的子串
    for (int len = 2; len <= n; ++len)
    {
        for (int l = 0; l + len - 1 < n; ++l)
        {
            int r = l + len - 1;
            if (len == 2)
                isPal[l][r] = (s[l] == s[r]);
            else
                isPal[l][r] = (s[l] == s[r] && isPal[l + 1][r - 1]);
        }
    }

    // dp[i]：前i个字符 s[0..i-1] 的最小分割次数
    int* dp = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i <= n; ++i)
        dp[i] = INT_MAX;
    dp[0] = -1;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if ((isPal[j][i - 1]) && (dp[j] + 1 < dp[i]))
                dp[i] = dp[j] + 1;
        }
    }

    int result = dp[n];

    // 释放内存
    for (int i = 0; i < n; ++i)
        free(isPal[i]);
    free(isPal);
    free(dp);

    return result;
}
// @lc code=end

